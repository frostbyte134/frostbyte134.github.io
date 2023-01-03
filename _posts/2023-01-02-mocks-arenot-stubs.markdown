---
layout: post
title:  "Mocks Aren't Stubs"
date:   2023-01-01 07:00:05 +0800
categories: coding
use_math: true
tags: coding
---

Keywors: Test double, state / behavior verification, Mock, Stub, classical / Mockiest TDD

https://martinfowler.com/articles/mocksArentStubs.html

xUnit tests follow a typical four phase sequence: setup, exercise, verify, teardown

`SUT`
- System Under Test
- primary object, object under test

`collaborators`
- objects other than SUT. SUT has depenency on these to perform test

`state verification`
- we determine whether the exercised method worked correctly by examining the state of the SUT and its collaborators after the method was exercised

the collaborator isn't a warehouse object, instead it's a mock warehouse - technically an instance of the class Mock.

As we'll see, mock objects enable a different approach to verification.
- state / behavior verification

### Tests with Mock Objects

```
public class OrderInteractionTester extends MockObjectTestCase {
  private static String TALISKER = "Talisker";

  public void testFillingRemovesInventoryIfInStock() {
    //setup - data
    Order order = new Order(TALISKER, 50);
    Mock warehouseMock = new Mock(Warehouse.class);
    
    //setup - expectations
    warehouseMock.expects(once()).method("hasInventory")
      .with(eq(TALISKER),eq(50))
      .will(returnValue(true));
    warehouseMock.expects(once()).method("remove")
      .with(eq(TALISKER), eq(50))
      .after("hasInventory");

    //exercise
    order.fill((Warehouse) warehouseMock.proxy());
    
    //verify
    warehouseMock.verify();
    assertTrue(order.isFilled());
  }

  public void testFillingDoesNotRemoveIfNotEnoughInStock() {
    Order order = new Order(TALISKER, 51);    
    Mock warehouse = mock(Warehouse.class);
      
    warehouse.expects(once()).method("hasInventory")
      .withAnyArguments()
      .will(returnValue(false));

    order.fill((Warehouse) warehouse.proxy());

    assertFalse(order.isFilled());
  }
  ```

In setup phase,
- data part: prepare SUT / collaborators(mocks)
- expectations part: creates expectations on the mock object. __The expectations indicate which methods should be called on the mocks when the SUT is exercised.__

exercise: run SUT

in verify phase,
1. verify SUT as before
2. additionally, verify mocks 

The key difference here is how we verify that the order did the right thing in its interaction with the warehouse
1. With `state verification` we do this by asserts against the warehouse's state
2. Mocks use `behavior verification`, where we instead check to see if the order made the correct calls on the warehouse. We do this check by telling the mock what to expect during setup and asking the mock to verify itself during verification. Only the order is checked using asserts, and if the method doesn't change the state of the order there's no asserts at all


personal summary: Mock checks whether the correct (fake) behaviors were performed on mock objects, hence behavior verification 


### The Difference Between Mocks and Stubs

When you're doing testing like this, you're focusing on one element of the software at a time - hence the common term `unit testing`.  
The problem is that to make a single unit work, you often need other units.

In the two styles of testing I've shown above, the first case uses a real warehouse object and the second case uses a mock warehouse, which of course isn't a real warehouse object
- Using mocks is one way to not use a real warehouse in the test, but there are other forms of unreal objects used in testing like this.


Meszaros uses the term 
- `Test Double` as the generic term for any kind of pretend object used in place of a real object for testing purposes. The name comes from the notion of a Stunt Double in movies.

Meszaros then defined five particular kinds of double:
- `Dummy` objects are passed around but never actually used. Usually they are just used to fill parameter lists.
- `Fake` objects actually have working implementations, but usually take some shortcut which makes them not suitable for production (an in memory database is a good example).
- `Stubs` provide canned answers to calls made during the test, usually not responding at all to anything outside what's programmed in for the test.
- `Spies` are stubs that also record some information based on how they were called. One form of this might be an email service that records how many messages it was sent.
- `Mocks` are what we are talking about here: objects pre-programmed with expectations which form a specification of the calls they are expected to receive.

Of these kinds of doubles, only mocks insist upon behavior verification. The other doubles can, and usually do, use state verification. Mocks actually do behave like other doubles during the exercise phase, as they need to make the SUT believe it's talking with its real collaborators - but mocks differ in the setup and the verification phases.


Here we can begin to see the difference between mocks and stubs. If we were writing a test for this mailing behavior, we might write a simple stub like this.
```java
public interface MailService {
  public void send (Message msg);
}
public class MailServiceStub implements MailService {
  private List<Message> messages = new ArrayList<Message>();
  public void send (Message msg) {
    messages.add(msg);
  }
  public int numberSent() {
    return messages.size();
  }
}                            
```     
We can then use state verification on the stub like this.

```java
class OrderStateTester...

  public void testOrderSendsMailIfUnfilled() {
    Order order = new Order(TALISKER, 51);
    MailServiceStub mailer = new MailServiceStub();
    order.setMailer(mailer);
    order.fill(warehouse);
    assertEquals(1, mailer.numberSent());
  }
```

Of course this is a very simple test - only that a message has been sent. We've not tested it was sent to the right person, or with the right contents, but it will do to illustrate the point.

Using mocks this test would look quite different.
```java
class OrderInteractionTester...

  public void testOrderSendsMailIfUnfilled() {
    Order order = new Order(TALISKER, 51);
    Mock warehouse = mock(Warehouse.class);
    Mock mailer = mock(MailService.class);
    order.setMailer((MailService) mailer.proxy());

    mailer.expects(once()).method("send");
    warehouse.expects(once()).method("hasInventory")
      .withAnyArguments()
      .will(returnValue(false));

    order.fill((Warehouse) warehouse.proxy());
  }
}
```

in both cases, used a test double instead of the real mail service
- but stub used state verification, which requred addition method `numberSent()` needed to be implemented (specially for stub obj)
- Mock used behavior verification


Mock objects always use behavior verification, a stub can go either way. Meszaros refers to stubs that use behavior verification as a Test Spy. 


### Classical / Mockiest TDD


The `classical TDD`
- uses real objects if possible and a double if it's awkward to use the real thin
- So a classical TDDer would use a real warehouse and a double for the mail service. The kind of double doesn't really matter that much.

A `mockist TDD` practitioner 
- will always use a mock for any object with interesting behavior. In this case for both the warehouse and the mail service.



### Choosing Between the Differences

read from here