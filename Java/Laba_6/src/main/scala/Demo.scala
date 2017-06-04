/**
  * Created by Knazz on 17.04.2017.
  */
package main.scala

import scala.collection.mutable.ArrayBuffer

object Demo {
  def funcList(list: List[Int], f: (List[Int]) => Int): Int = {
    f(list)
  }

  def sumFunc(list: List[Int]): Int = {
    list.filter(_ > 0).sum
  }

  def natural(N: Int, list: List[Int], i: Int): Any = {
    if (i == N + 1)
      list
    else if ((i % 2 != 0) && (i % 3 != 0) && (i % 5 != 0))
      natural(N, list ++ List(i), i + 1)
    else
      natural(N, list, i + 1)
  }

  def generateMatrix(N: Int, i: Int, list: List[Int]): List[Int] = {
    if (i == N)
      list
    else {
      val num = (Math.random() * 10 + 1).toInt
      generateMatrix(N, i + 1, list ++ List(num))
    }
  }

  def sortMt(matrix: Array[Array[Int]]) = {
    var temp = new ArrayBuffer[Int]
    for (i <- 0 until matrix.length) {
      for (j <- 0 until matrix(0).length) {
        temp.append(matrix(i)(j))
      }
    }
    temp = temp.sortWith(_ < _)
    var ind = 0
    for (i <- 0 until matrix.length) {
      if (i % 2 == 0) {
        for (j <- 0 until matrix(0).length) {
          matrix(i)(j) = temp(ind)
          ind += 1
        }
      }
      if (i % 2 == 1) {
        for (j <- (0 until matrix.length).reverse) {
          matrix(i)(j) = temp(ind)
          ind += 1
        }
      }
    }
    matrix
  }
}