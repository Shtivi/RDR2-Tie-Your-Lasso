using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using RDR2;
using RDR2.UI;
using RDR2.Native;
using RDR2.Math;

namespace TieYourLasso
{
    public class AttachedRope
    {
        public Entity AttachedEntity1 { get; private set; }

        public  Entity AttachedEntity2 { get; private set; }
        public Rope Rope { get; private set; }

        public AttachedRope(Entity FirstEntity, Entity SecondEntity, string bone1, string bone2, float length, float minLength = 0)
        {
            var pos = FirstEntity.Position;
            int ropeId = Function.Call<int>(Hash.ADD_ROPE, pos.X, pos.Y, pos.Z, 0.0f, 0.0f, 0.0f, length, 14, length, minLength, 1.0f, 0, 1, true, 1.25f, true, 0, 0);
            Function.Call(Hash._0x462FF2A432733A44, ropeId, FirstEntity.Handle, SecondEntity.Handle, 0f, 0f, 0f, 0f, 0f, 0.0f, bone1, bone2);
            Function.Call(Hash.ACTIVATE_PHYSICS, ropeId);
            Function.Call(Hash._0x3C6490D940FF5D0B, ropeId, 0, 0, length, 0);

            this.Rope = new Rope(ropeId);
        }

        public void Delete()
        {
            Rope.Delete();
        }
    }
}
