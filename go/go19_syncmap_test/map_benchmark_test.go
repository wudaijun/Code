package mapbench

import (
	"math/rand"
	"testing"
	"time"
)

func BenchmarkMutexMapStoreParalell(b *testing.B) {
	b.RunParallel(func(pb *testing.PB) {
		r := rand.New(rand.NewSource(time.Now().Unix()))
		for pb.Next() {
			// The loop body is executed b.N times total across all goroutines.
			k := r.Intn(100000000)
			mutexMapStore(k, k)
		}
	})
}

func BenchmarkSyncMapStoreParalell(b *testing.B) {
	b.RunParallel(func(pb *testing.PB) {
		r := rand.New(rand.NewSource(time.Now().Unix()))
		for pb.Next() {
			// The loop body is executed b.N times total across all goroutines.
			k := r.Intn(100000000)
			syncMapStore(k, k)
		}
	})
}

func BenchmarkMutexMapLoadParalell(b *testing.B) {
	b.RunParallel(func(pb *testing.PB) {
		r := rand.New(rand.NewSource(time.Now().Unix()))
		for pb.Next() {
			// The loop body is executed b.N times total across all goroutines.
			//k := r.Int()
			k := r.Intn(100000000)
			mutexMapLoad(k)
		}
	})
}

func BenchmarkSyncMapLoadParalell(b *testing.B) {
	b.RunParallel(func(pb *testing.PB) {
		r := rand.New(rand.NewSource(time.Now().Unix()))
		for pb.Next() {
			// The loop body is executed b.N times total across all goroutines.
			k := r.Intn(100000000)
			syncMapLoad(k)
		}
	})
}

func BenchmarkMutexMapDeleteParalell(b *testing.B) {
	b.RunParallel(func(pb *testing.PB) {
		r := rand.New(rand.NewSource(time.Now().Unix()))
		for pb.Next() {
			// The loop body is executed b.N times total across all goroutines.
			k := r.Intn(100000000)
			mutexMapDelete(k)
		}
	})
}

func BenchmarkSyncMapDeleteParalell(b *testing.B) {
	b.RunParallel(func(pb *testing.PB) {
		r := rand.New(rand.NewSource(time.Now().Unix()))
		for pb.Next() {
			// The loop body is executed b.N times total across all goroutines.
			k := r.Intn(100000000)
			syncMapDelete(k)
		}
	})
}
