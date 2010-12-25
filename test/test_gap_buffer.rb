class TestGapBuffer < Test::Unit::TestCase
  def test_initialize
    assert_equal 20, GapBuffer::GAP_SIZE
    assert_instance_of GapBuffer, GapBuffer.new(10)
    assert_equal 10, GapBuffer.new(10).gap_size
    assert_equal 20, GapBuffer.new.gap_size
  end

  def test_size
    gb = GapBuffer.new
    assert_equal 0, gb.size
  end

  def test_gap_size
    gb = GapBuffer.new
    assert_equal 20, gb.gap_size
  end

  def test_print
    gb = GapBuffer.new
    gb.print
  end

  def test_append
    gb = GapBuffer.new
    gb << 'test'
    assert_equal 'test', gb.to_s
    assert_equal 5, gb.offset
  end

  def test_offset
    gb = GapBuffer.new
    assert_equal 0, gb.offset
    gb << 'test'
    assert_equal 5, gb.offset
    gb << 'buffer'
    assert_equal 12, gb.offset
  end

  def test_offset_equals
    gb = GapBuffer.new
    assert_equal 0, gb.offset
    gb.offset = 5
    assert_equal 5, gb.offset
  end

  def test_move
    gb = GapBuffer.new
    assert_equal 0, gb.offset
    gb.offset = 5
    gb.move
  end

  def test_get
    gb = GapBuffer.new
    gb << 'test'
    gb.offset = 2
    assert_equal 's', gb.get
    assert_equal 2, gb.offset
  end

  def test_previous
    gb = GapBuffer.new
    gb << 'test'
    assert_equal '', gb.previous
    gb.offset = 2
    assert_equal 'e', gb.previous
    assert_equal 1, gb.offset
  end

  def test_next
    gb = GapBuffer.new
    gb << 'test'
    assert_equal '', gb.previous
    gb.offset = 2
    assert_equal 't', gb.next
    assert_equal 3, gb.offset
  end

  def test_delete
    gb = GapBuffer.new
    gb << 'test'
    assert_equal '', gb.previous
    gb.offset = 2
    gb.delete(2)
    assert_equal 'test', gb.to_s
  end

  def test_to_s
    gb = GapBuffer.new
    gb << 'test'
    assert_equal 'test', gb.to_s
  end

  def test_replace
    gb = GapBuffer.new
    gb << 'test'
    gb.offset = 2
    gb.replace('x')
    assert_equal 'text', gb.to_s
  end

  def test_insert
    gb = GapBuffer.new
    gb << 'test'
    gb.offset = 2
    gb.insert('x')
    assert_equal 'text', gb.to_s
    gb.insert('zz')
    assert_equal 'tezt', gb.to_s
  end

  def test_insert_at
    gb = GapBuffer.new
    gb << 'test'
    gb.insert_at(2, 'x')
    assert_equal 'text', gb.to_s
    gb.insert_at(3, 'z')
    assert_equal 'texz', gb.to_s
  end

  def test_delete_at
    gb = GapBuffer.new
    gb << 'test'
    gb.insert_at(2, 'x')
    assert_equal 'text', gb.to_s
    gb.delete_at(2)
    assert_equal 'text', gb.to_s
  end

  def test_put
    gb = GapBuffer.new
    gb << 'test'
    gb.offset = 2
    gb.put('x')
    assert_equal 'text', gb.to_s
    gb.put('zzzzz')
    assert_equal 'texz', gb.to_s
  end
end