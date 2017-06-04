/**
  * Created by Knazz on 17.04.2017.
  */
package test.scala

import org.junit.runner.RunWith
import org.scalatest.junit.JUnitRunner
import org.scalatest.FunSuite
import main.scala.Demo
import org.scalatest.FunSuite
@RunWith(classOf[JUnitRunner])
class MatchTest extends FunSuite {

  //Testing usual recursion
  test("notTailRec should return 011000 if 0 is provided") {
    val s = Demo.convert(0)
    val newList = Demo.codeTo(s, 0, s.size, List())
    assert(newList.equals("011000"))
  }
  test("notTailRec should return 011000100110 if 25 is provided") {
    val s = Demo.convert(25)
    val newList = Demo.codeTo(s, 0, s.size, List())
    assert(newList.equals("011000100110"))
  }

  test("notTailRec should return 100010011000011000 if 1024 is provided") {
    val s = Demo.convert(1024)
    val newList = Demo.codeTo(s, 0, s.size, List())
    assert(newList.equals("100010011000011000"))
  }

  test("notTailRec should return 011000001100100110101001 if -25381 is provided") {
    val s = Demo.convert(-25381)
    val newList = Demo.codeTo(s, 0, s.size, List())
    assert(newList.equals("011000001100100110101001"))
  }
}
