/**
  * Created by Knazz on 17.04.2017.
  */
package test.scala

import org.junit.runner.RunWith

import org.scalatest.junit.JUnitRunner

import org.scalatest.FunSuite

import main.scala.Demo
//@RunWith(classOf[JUnitRunner])
object MatchTest extends App {

  /*//Testing usual recursion
  test("notTailRec should return '2, 3, 4, 5, 6' if '1, 7' is provided") {
    val s = Demo.notTailRec(1, 7)
    assert(s.equals(List(2, 3, 4, 5, 6)))
  }

  test("notTailRec should return '-1, 0, 1, 2, 3, 4, 5, 6' if '-1.6, 6.7' is provided") {
    val s = Demo.notTailRec(-1.6, 6.7)
    assert(s.equals(List(-1, 0, 1, 2, 3, 4, 5, 6)))
  }

  test("notTailRec should return empty List if '5, 5' is provided") {
    val s = Demo.notTailRec(5, 5)
    assert(s.equals(List()))
  }

  test("notTailRec should return '-4, -3, -2, -1, 0' if '-5, 1' is provided") {
    val s = Demo.notTailRec(-5, 1)
    assert(s.equals(List(-4, -3, -2, -1, 0)))
  }

  test("notTailRec should return empty List if '7, -6' is provided") {
    val s = Demo.notTailRec(7, -6)
    assert(s.equals(List()))
  }

  //Testing tail recursion, tests are the same
  test("tailRecNumbers should return '2, 3, 4, 5, 6' if '1, 7' is provided") {
    val s = Demo.tailRecNumbers(1, 7, List())
    assert(s.equals(List(2, 3, 4, 5, 6)))
  }

  test("tailRecNumbers should return '-1, 0, 1, 2, 3, 4, 5, 6' if '-1.6, 6.7' is provided") {
    val s = Demo.tailRecNumbers(-1.6, 6.7, List())
    assert(s.equals(List(-1, 0, 1, 2, 3, 4, 5, 6)))
  }

  test("tailRecNumbers should return empty List if '5, 5' is provided") {
    val s = Demo.tailRecNumbers(5, 5, List())
    assert(s.equals(List()))
  }

  test("tailRecNumbers should return '-4, -3, -2, -1, 0' if '-5, 1' is provided") {
    val s = Demo.tailRecNumbers(-5, 1, List())
    assert(s.equals(List(-4, -3, -2, -1, 0)))
  }

  test("tailRecNumbers should return empty List if '7, -6' is provided") {
    val s = Demo.tailRecNumbers(7, -6, List())
    assert(s.equals(List()))
  }

  test("tailRecNumbers should return empty List if 1234 is provided") {
    val s = Demo.reverseFun(14567)
    assert(s.equals(76541
    ))
  }*/

  var s1 = Demo.createTree(6, 6, 0)
  println(s1);
}
