// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quelles questions avez-vous?","Comment puis-je vous aider ?"),"Tu as essayé de me poser cette question il n'y a pas longtemps...","Oui, laissez-moi deviner... Encore à tourner en rond ?","Ecoutez, je m'occupe des finances ici, je ne réponds pas aux questions...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Je n'ai rien à dire pour le moment."),"Où donc est passée ma mémoire...","Vous avez deviné, je suis désolé...","Je comprends...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Je me rends à Blueweld avec une cargaison de vin. Mais j'ai appris d'un capitaine qu'à Blueweld, la demande de café a augmenté et je ne sais pas pourquoi. Je pense à vendre le vin et à acheter du café à la place, mais je n'ai pas assez d'argent pour remplir ma cale à ras bord. Pourrais-je vous emprunter de l'argent avec intérêt ?";
                link.l1.go = "UsurerDone";
            }
		break;
		
		case "UsurerDone":
			dialog.text = "Crédit pour un commerçant réputé, pas de problème. De quel montant avez-vous besoin ? Parlons-en.";
			link.l1 = "D'accord. Je chargerai la cale et compterai combien d'espace il reste. Ensuite, je déterminerai la quantité qui me manque et je reviendrai vers vous, si le besoin se fait sentir.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = int(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-13");
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
