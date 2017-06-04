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
object MatchTest extends App {

  /*//Testing usual recursion
  test("notTailRec should return 6 if List(1, 2, 3, -4, -6, 0) is provided") {
    val s = Demo.funcList(List(1, 2, 3, -4, -6, 0), Demo.sumFunc)
    assert(s.equals(6))
  }

  test("notTailRec should return 11 if List(1, 2, 3, 4, 1) is provided") {
    val s = Demo.funcList(List(1, 2, 3, 4, 1), Demo.sumFunc)
    assert(s.equals(11))
  }

  test("notTailRec should return 0 if List(-10, -4, -6, -7, 2) is provided") {
    val s = Demo.funcList(List(-10, -4, -6, -7, -2), Demo.sumFunc)
    assert(s.equals(0))
  }

  test("notTailRec should return 0 if empty List is provided") {
    val s = Demo.matrixSort(3)
    assert(s.equals(List(1, 7, 11, 13)))
  }*/
  val s = Demo.sortMt(Array(Array(1,2,3), Array(4,5,6), Array(7,8,9)))
}
