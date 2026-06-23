// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quelles questions avez-vous ?","Comment puis-je vous aider ?"),"Tu as essayé de me poser une question il y a peu...","Je n'ai jamais rencontré de gens avec une telle curiosité dans mon chantier naval ou ailleurs dans cette ville.","Pourquoi toutes ces questions ? Mon travail est de construire des navires. Occupons-nous de cela.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Je n'ai rien à dire pour le moment."),"Humph, où est passée ma mémoire...","Hm, bien...","Allez-y...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		case "helendrinking_buy_rainbow":
			dialog.text = "... un choix digne, monsieur. Alors, c'est un accord ?";
			link.l1 = "Ou-oui! À votre santé! Emballez-le et envoyez-le sur le quai. Et dépêchez-vous, une dame m'attend dans la rue !";
			link.l1.go = "helendrinking_buy_rainbow_1";
			locCameraFromToPos(0.36, 1.86, 1.15, true, 2.06, -0.20, -4.38);
		break;
		
		case "helendrinking_buy_rainbow_1":
			dialog.text = "Cinquante mille pièces d’argent pour tout, monsieur.";
			if (int(pchar.money) >= 55000) {
				link.l1 = "B-combien avez-vous dit ? C-cinquante mille ? Eh bien, comptez-le vous-même ! Et prenez cinq mille de plus comme pourboire. Allons-y !";
				link.l1.go = "helendrinking_buy_rainbow_yes";
			}
			
			link.l2 = "Non-non, je peux être un homme riche, hic ! ...mais je ne paierai pas autant. Non, monsieur ! Adieu, batelier.";
			link.l2.go = "helendrinking_buy_rainbow_no";
		break;
		
		case "helendrinking_buy_rainbow_yes":
			dialog.text = "Merci, monsieur. Puisse-t-elle vous servir fidèlement !";
			link.l1 = "Bonjour, capitaine.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			AddMoneyToCharacter(pchar, -55000);
			pchar.questTemp.HelenDrinking.BoughtRainbow = true;
			
			AddDialogExitQuestFunction("HelenDrinking_GoToPerlas");
		break;
		
		case "helendrinking_buy_rainbow_no":
			dialog.text = "Ouais, dégage, riche type. On a fermé il y a trois heures.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToPerlas");
		break;
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
