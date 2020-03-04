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
    public class RopesFactory
    {
        private SpawnedPropsManager PropsManager { get; set; }

        public RopesFactory(SpawnedPropsManager spawnedPropsManager)
        {
            this.PropsManager = spawnedPropsManager;
        }

        public AttachedRope AttachEntityToMapPosition(Vector3 MapPosition, Entity AttachedEntity, float length = 0, string BoneName = null)
        {
            var mapProp = PropsManager.CreateProp("p_shotGlass01x", MapPosition);
            mapProp.FreezePosition = true;
            mapProp.IsVisible = true;

            if (length <= 0)
            {
                length = AttachedEntity.Position.DistanceTo(MapPosition);
            }

            var rope = new AttachedRope(AttachedEntity, mapProp, BoneName, null, length, length);
            return rope;
        }

        public AttachedRope AttachEntities(Entity entity1, Entity entity2, float length = 0, string bone1 = null, string bone2 = null)
        {
            if (length <= 0)
            {
                length = entity1.Position.DistanceTo(entity2.Position);
            }

            var rope = new AttachedRope(entity1, entity2, bone1, bone2, length, length);
            return rope;
        }
    }
}
