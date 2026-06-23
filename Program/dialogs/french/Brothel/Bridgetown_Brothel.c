// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quel genre de questions, "+GetSexPhrase("jeune homme","jeune demoiselle")+" ?","Que désirez-vous, "+GetSexPhrase("bel étalon","jolie créature")+" ? Demandez donc."),"Encore des questions?","Hihi, si ça vous est égal - des questions...",""+GetSexPhrase("Hum, pourquoi vous ne choisissez pas une jolie fille ? Je commence à avoir des soupçons à votre sujet...","Hm, choisissez donc une fille par vous-même. Nous n'avons pas de garçons ici, j'en ai peur, hi-hi...")+"","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis, excusez-moi.","En fait, peu importe..."),"Je... mes excuses, je n'ai pas de questions, pour l'instant.","Vous avez raison, c'est déjà la troisième fois. Pardonnez-moi.","Peut-être la prochaine fois, Madame.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "J'ai acheté une cargaison d'acajou à vendre et je me dirige vers Blueweld. Il nous reste un sacré bout de chemin, et mes hommes sont peu nombreux et impatients... Combien cela coûterait-il pour laisser cinquante marins se reposer ici pour la nuit ?";
                link.l1.go = "BrothelDone";
            }
		break;
		
		case "BrothelDone":
			dialog.text = "Cinquante marins - quinze mille.";
			link.l1 = "Une certaine somme... Je vais y réfléchir.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = int(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-7");
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
