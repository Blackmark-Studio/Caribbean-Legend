// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quelles questions avez-vous ?","Comment puis-je vous aider ?"),"Vous avez essayé de me poser une question il y a peu de temps...","Je n'ai jamais rencontré de gens avec une telle curiosité dans mon chantier naval ou ailleurs dans cette ville.","Pourquoi toutes ces questions ? Mon métier, c'est de construire des navires. Occupons-nous de cela.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Je n'ai rien à dire pour le moment."),"Humph, où est passée ma mémoire...","Hm,   eh bien...","Allez-y...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Je suis en route vers Blueweld avec une cargaison de café et j'aimerais acheter d'autres marchandises, mais voici le problème : sur cette brigantine, que j'ai achetée à un chien de guerre, il y a une quantité abominable de canons lourds, un total de 24. Je ne suis pas en route pour une guerre, tu sais. J'aimerais te les vendre tous et acheter 12 canons de six livres, largement suffisants pour effrayer quelques pirates. Et le reste de l'espace que j'ai, je le remplirai de marchandises.";
                link.l1.go = "ShipyardDone";
			}
		break;
		
		case "ShipyardDone":
			dialog.text = "Oui, allez-y, vendez-les. J'ai toujours assez de six-livres, mais j'ai toujours un problème avec les canons lourds, puisque tout le monde les achète tout le temps et personne ne veut les vendre, à moins qu'ils ne soient complètement cassés, donc je vous paierai un bon prix pour eux s'ils sont bien sûr encore en état de marche.";
			link.l1 = "Wow, formidable ! Je vais donner des ordres tout de suite.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = int(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-10");
			DelLandQuestMark(npchar);
			if (int(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7)
			{
			AddQuestRecord("Holl_Gambit", "2-6");
			pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
			DelMapQuestMarkCity("Bridgetown");
			pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
				//if(int(RealShips[int(pchar.ship.type)].basetype) != SHIP_VALCIRIA || GetCompanionQuantity(pchar) > 1) AddDialogExitQuestFunction("FailVanBergInWorld");
				//else AddDialogExitQuestFunction("CreateVanBergInWorld");
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
