using RDR2;
using RDR2.Math;
using RDR2.Native;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TieYourLasso
{
    public class SpawnedPropsManager
    {
        public List<Prop> Props { get; private set; }

        public SpawnedPropsManager()
        {
            this.Props = new List<Prop>();
        }

        public Prop CreateProp(string model, Vector3 Position)
        {
            return CreateProp(model, Position, Vector3.Zero);
        }

        public Prop CreateProp(string model, Vector3 Position, Vector3 Rotation)
        {
            var prop = new Prop(Function.Call<int>(Hash.CREATE_OBJECT, new Model(model), Position.X, Position.Y, Position.Z, false, false, true));
            prop.Rotation = Rotation;
            this.Props.Add(prop);
            return prop;
        }

        public void Delete(Prop instance)
        {
            if (instance == null)
            {
                return;
            }
          
            this.Props.Remove(instance);

            if (instance.Exists())
            {
                instance.Delete();
            }
        }

        public void DeleteAll()
        {
            for (int i = Props.Count - 1; i >= 0; i--)
            {
                var prop = this.Props[i];
                if (prop.Exists())
                {
                    prop.Delete();
                    Props.RemoveAt(i);
                }
            }
        }
    }
}
