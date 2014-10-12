using System;

namespace SimplerSoccer {
    public class RandomGenerator {

        private Random random;

        public RandomGenerator() {
            random = new Random((int)DateTime.Now.Ticks);
        }

        public float InRange(float min, float max) {
            return min + (float)random.NextDouble() * (max - min);
        }

    }
}

