// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que veux-tu ? Demande donc.","Je vous écoute, quelle est la question ?"),"C'est la deuxieme fois que vous essayez de demander...","C'est la troisième fois que vous essayez encore de demander...","Quand cela va-t-il se terminer ?! Je suis un homme occupé, travaillant sur les affaires de la colonie et vous essayez encore de demander quelque chose !","bloc",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Pas maintenant. Mauvais endroit et mauvais moment."),"Vrai... Mais plus tard, pas maintenant...","Je demanderai... Mais un peu plus tard...","Je suis désolé, "+GetAddress_FormToNPC(NPChar)+"... ",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "J'ai conclu une affaire lucrative à la Martinique et maintenant je prévois de naviguer vers Blueweld. Je veux acheter du bois rouge et du café dans votre colonie. De plus, mon brigantin ne peut pas contenir autant de cargaison que je souhaite acheter, donc j'ai besoin d'acheter une flûte ici à votre chantier naval. Pourrais-je avoir votre assistance dans ces affaires ?";
                link.l1.go = "MayorDone";
            }
		break;
		
		case "MayorDone":
			dialog.text = "Mon aide ? Notre marchand est un homme très honnête, je doute donc qu'il tente de vous duper. Parlez au maître de port à propos de la flûte, il vous aidera dans cette affaire. Et si vous rencontrez des problèmes malgré tout, alors vous devriez venir me voir. Je suis intéressé par l'avancement des relations commerciales avec notre colonie et je vous apporterai tout mon soutien. \nDe plus, j'organise un banquet ce soir, tous les notables de Bridgetown seront présents. Vous devriez venir aussi, capitaine.";
			link.l1 = "Merci pour votre invitation, mais malheureusement je suis trop occupé. Adieu et merci pour votre sollicitude !";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = int(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-8");
			DelLandQuestMark(npchar);
			if (int(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7)
			{
			AddQuestRecord("Holl_Gambit", "2-6");
			pchar.questTemp.HWIC.Eng = "SeekVanBerg";
			pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
			DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
				//if(int(RealShips[int(pchar.ship.type)].basetype) != SHIP_VALCIRIA || GetCompanionQuantity(pchar) > 1) AddDialogExitQuestFunction("FailVanBergInWorld");
				//else AddDialogExitQuestFunction("CreateVanBergInWorld");
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
