using System;
using System.Collections.Generic;

namespace Sandbox
{
    class Parent : IFinangler
    {
        List<Child> _children;

        public Parent()
        {
            _children = new List<Child>
            {
                new Child(),
                new Child(),
                new Child(),
            };
        }

        public void DoIt()
        {
            foreach (var child in _children)
            {
                child.DoIt(this);
            }
        }

        public void Finangle()
        {
            Console.WriteLine("Parent finangled by child");
        }
    }
}
