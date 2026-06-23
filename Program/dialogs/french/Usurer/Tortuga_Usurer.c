// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quelles questions avez-vous ?","Comment puis-je vous aider?"),"Vous avez essayé de me poser cette question il n'y a pas longtemps...","Oui, laissez-moi deviner... Encore une fois à tourner en rond ?","Ecoutez, je m'occupe des finances ici, je ne réponds pas aux questions...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Je n'ai rien à dire pour le moment."),"Où diable est passée ma mémoire...","Vous avez deviné, je suis désolé...","Je comprends...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		case "tonzag_bail":
			dialog.text = "Bonjour, Capitaine. Comment puis-je, ainsi que mon entreprise, vous être utile ?";
			link.l1 = "Je voudrais faire un don au fonds de pension de l'illustre garnison de Tortuga.";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_1":
			dialog.text = "Je comprends. Cela devient assez courant de nos jours ! Combien devez-vous... je veux dire, souhaitez-vous donner ?";
			link.l1 = pchar.questTemp.TonzagQuest.Bail+"  doublons. Dites-moi, acceptez-vous en pesos ?";
			link.l1.go = "tonzag_bail_2";
		break;
		
		case "tonzag_bail_2":
			dialog.text = "Bien sûr, cependant, cela vous coûtera un peu plus cher. Laissez-moi vous expliquer exactement... "+pchar.questTemp.TonzagQuest.Bail+"  doubloons seront "+int(pchar.questTemp.TonzagQuest.Bail)* 150+" pesos.";
			if (PCharDublonsTotal() >= int(pchar.questTemp.TonzagQuest.Bail) || int(pchar.money) >= int(pchar.questTemp.TonzagQuest.Bail) * 150) {
				link.l1 = "Un peu plus cher, dites-vous ? Tenez, voici le montant complet requis.";
				link.l1.go = "tonzag_bail_give";
			} else {
				link.l1 = "Un peu plus cher, dites-vous? Malheureusement, je n'ai pas cette somme pour le moment. Est-il possible de prendre un prêt pour cette affaire?";
				link.l1.go = "tonzag_bail_loan";
			}
		break;
		
		case "tonzag_bail_give":
			dialog.text = "Magnifique. Nous informerons immédiatement votre contrepartie ! Adieu, Capitaine. Et... bonne chance, nous attendons votre performance depuis longtemps.";
			link.l1 = "Adieu.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			if (PCharDublonsTotal() >= int(pchar.questTemp.TonzagQuest.Bail)) {
				RemoveDublonsFromPCharTotal(int(pchar.questTemp.TonzagQuest.Bail));
			} else {
				AddMoneyToCharacter(pchar, -(int(pchar.questTemp.TonzagQuest.Bail) * 150));
			}
			sld = CharacterFromID("TortugaJailOff");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "tonzag_bailed";
		break;
		
		case "tonzag_bail_loan":
			dialog.text = "Une telle opportunité vous est toujours offerte, Capitaine ! Disons, avec le retour de deux cent mille pesos en six mois ?";
			link.l1 = "Je n'ai pas le choix. Où dois-je signer ?";
			link.l1.go = "tonzag_bail_give";
			
			pchar.quest.loans.tortuga.sum = 200000;
			pchar.quest.loans.tortuga.interest = 0;
			pchar.quest.loans.tortuga.period = 6;
			pchar.quest.loans.tortuga.StartDay = GetDataDay();
			pchar.quest.loans.tortuga.StartMonth = GetDataMonth();
			pchar.quest.loans.tortuga.StartYear = GetDataYear();
			pchar.quest.loans.tortuga.StartTime = GetTime();
			SetTimerCondition("Loans_Tortuga", 0, int(pchar.quest.loans.tortuga.period), 0, false);
			pchar.quest.Loans_Tortuga.CityId = "Tortuga";
			pchar.quest.Loans_Tortuga.win_condition = "LoansForAll";
			
			AddMoneyToCharacter(pchar, int(pchar.questTemp.TonzagQuest.Bail) * 150);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
