// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Allez-y, que désirez-vous?","Nous en parlions justement. Vous devez avoir oublié...","C'est la troisième fois aujourd'hui que vous parlez d'une question...","Ecoutez, ceci est une boutique. Les gens achètent des trucs ici. Ne me dérangez pas !","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tu sais, "+NPChar.name+"Peut-être la prochaine fois.","Ah, j'ai oublié pour une raison...","Oui, c'est vraiment la troisième fois...","Hm, je ne veux pas...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Ecoutez, un petit oiseau m'a dit que les prix du bois rouge et du cacao à Belize vont bientôt monter en flèche. J'ai récemment conclu une bonne affaire et rempli ma bourse de doublons, héhé... J'aimerais acquérir un peu de cette marchandise. Puis-je compter sur une remise ?";
                link.l1.go = "StoreDone";
            }
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "barbados1")
			{
				link.l1 = "Un galion nommé 'Admirable' a récemment accosté à votre colonie sous le commandement du capitaine Gaius Marchais. Dites-moi, aurait-il pu se ravitailler en munitions ici ou en marchandises à revendre ?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "StoreDone":
			dialog.text = "Eh bien, monsieur, si le lot est vraiment grand, alors bien sûr, nous pouvons discuter d'une remise raisonnable.";
			link.l1 = "Merveilleux ! J'ai entendu dire qu'un nouveau flûte devrait être mis en vente au chantier naval d'un jour à l'autre. J'attendrai et j'achèterai ce navire. Même si j'ai retiré tous les canons de ma brigantine, il n'y a toujours pas assez de place dans ma cale pour toutes ces marchandises ! Je passerai plus tard !";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = int(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-11");
			DelLandQuestMark(npchar);
			if (int(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7)
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Ah ! Je me souviens de ce drôle de type ! Il a cru à quelques stupides ragots disant que la Guadeloupe aurait désespérément besoin de vanille parce qu'une grande caravane de marchands européens ferait une halte là-bas pour acheter autant d'épices qu'ils pourraient en porter\nJ'entends de telles absurdités chaque mois, mais Marchais a pris cela très au sérieux. Il a passé une semaine ici, m'a dit de rassembler assez de vanille pour remplir ses cales\nIl semble qu'il ait dépensé chaque sou pour cela. Je me sens mal pour cet homme, mais je ne peux pas empêcher les hommes de devenir fous s'ils le souhaitent.";
			link.l1 = "Alors, il pourrait être en Guadeloupe en ce moment ?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Très probablement. Car il continuera d'attendre ses 'marchands' fantaisistes jusqu'à la seconde venue du Christ et il ne fera que perdre de l'argent en vendant de la vanille. S'il est sage, il restera à Basse-Terre jusqu'à ce que la demande de vanille augmente ou jusqu'à ce qu'il découvre avec certitude un autre endroit où elle est plus nécessaire.";
			link.l1 = "Oui. Merci, tu m'as beaucoup aidé !";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "14");
			pchar.questTemp.Guardoftruth = "guadeloupe";
			pchar.quest.GuardOT_guadeloupe.win_condition.l1 = "location";
			pchar.quest.GuardOT_guadeloupe.win_condition.l1.location = "guadeloupe";
			pchar.quest.GuardOT_guadeloupe.function = "GuardOT_CreateTwoShips";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
