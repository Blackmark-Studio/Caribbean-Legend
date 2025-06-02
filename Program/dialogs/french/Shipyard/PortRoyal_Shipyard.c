// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quelles questions avez-vous ?","Comment puis-je vous aider ?"),"Vous avez essayé de me poser une question il y a un moment...","Je n'ai jamais rencontré des gens avec une telle curiosité dans mon chantier naval ou ailleurs dans cette ville.","Pourquoi toutes ces questions ? Mon travail est de construire des navires. Occupons-nous de ça.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Je n'ai rien à dire pour le moment."),"Umph, où est donc passée ma mémoire...","Hm, eh bien...","Allez-y...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx"))
            {
				if (pchar.questTemp.Mtraxx == "silk_2" || pchar.questTemp.Mtraxx == "silk_3")
				{
					link.l1 = "J'ai entendu dire que ce chantier naval s'occupe d'améliorer la vitesse de navigation du navire. Cela nécessite de la toile de voile en soie, qui est très rare. Voudriez-vous... en parler ?";
					link.l1.go = "mtraxx";
				}
			}
			if (CheckAttribute(npchar, "quest.upgradeship")) {
				link.l2 = "Je viens de la part de Mlle MacArthur, concernant...";
				link.l2.go = "helen_upgradeship";
			}
			
			if (CheckAttribute(npchar, "quest.upgradeship.money") && HelenCanUpgrade()) {
				link.l2 = "Commencez la révision du navire !";
				link.l2.go = "helen_upgradeship_money";
			}
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
            dialog.text = "Pourriez-vous être plus clair, jeune homme? Qu'est-ce qui vous amène exactement ici? Si vous souhaitez améliorer votre navire, passons aux affaires immédiatement.";
			link.l1 = "Pas entièrement. Les types de services que vous effectuez nécessitent des marchandises qui ne sont pas librement disponibles en magasin. J'aimerais vous offrir le même type de matériaux dont vous pourriez avoir besoin.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Eh bien, eh bien... Hum... Savez-vous que seules les autorités de cette colonie sont autorisées à traiter de tels biens stratégiques ? Vous êtes libre de fournir votre propre soie pour que je puisse améliorer votre navire, cependant, la vendre est strictement interdit. Tout comme l'acheter de moi - de telles activités seront lourdement sanctionnées.";
			link.l1 = "Eh bien, ceci n'est ni une boutique, ni un bureau de douane...";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "J'acquiers toute la toile de soie directement de mes clients, ou j'achète des quantités limitées avec une permission spéciale du gouverneur. Si vous n'avez plus de questions, alors s'il vous plaît, laissez-moi retourner à mon travail.";
			link.l1 = "Hmm... Très bien. Passez une bonne journée, maître.";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            DialogExit();
			AddQuestRecord("Roger_2", "5");
			pchar.questTemp.Mtraxx = "silk_4";
		break;
		
		case "helen_upgradeship":
			dialog.text = "Oh, I know! Lucky you, Captain. Is it about a complete overhaul of the ship? We'll take care of everything; our shipyard is on par with those in Plymouth!";
			link.l1 = "Je suppose que ce ne sera pas un service gratuit ?";
			link.l1.go = "helen_upgradeship_1";
		break;
		
		case "helen_upgradeship_1":
			dialog.text = "Bien sûr, Capitaine, de tels services ne peuvent être gratuits, même pour Cromwell ! Cependant, je tiens ma parole et ne prendrai que de l'argent - vous n'aurez pas à passer de la contrebande.";
			link.l1 = "Compréhensible. Combien?";
			link.l1.go = "helen_upgradeship_2";
		break;
		
		case "helen_upgradeship_2":
			dialog.text = "Ça dépend de la taille de votre navire amiral, Capitaine. Un navire de premier rang vous coûtera cinq mille doublons, et un de cinquième rang - seulement mille.";
			link.l1 = "D'accord, je viendrai te voir une fois que j'aurai pris une décision.";
			link.l1.go = "exit";
			
			npchar.quest.upgradeship.money = true;
		break;
		
		case "helen_upgradeship_money":
			dialog.text = "Excellent, maintenant j'ai tout ce dont j'ai besoin. Je vais commencer à travailler, alors.";
			link.l1 = "J'attends.";
			link.l1.go = "helen_upgradeship_money_1";
			
			iTemp = GetCharacterShipType(pchar);
			sld = GetRealShip(iTemp);
			iTemp = (7 - sti(sld.class)) * 1000;
			RemoveDublonsFromPCharTotal(iTemp);
		break;
		
		case "helen_upgradeship_money_1":
			AddTimeToCurrent(6, 30);
			dialog.text = "... Je suppose que c'est tout... La qualité est garantie.";
			link.l1 = "Merci ! Je vais aller voir ça.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenUpgradeShip2");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

bool HelenCanUpgrade() {
	int shipIndex = GetCharacterShipType(pchar);
	if (shipIndex == SHIP_NOTUSED) {
		return false;
	}
	
	sld = GetRealShip(shipIndex);
	if (sti(sld.class) == 7) {
		return false;
	}
	
	int cost = (7 - sti(sld.class)) * 1000;
	return (PCharDublonsTotal() >= cost);
}
