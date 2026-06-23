// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Allez-y, que voulez-vous?","Nous en parlions justement. Vous devez avoir oublié...","C'est la troisieme fois aujourd'hui que tu parles d'une question...","Ecoutez, c'est une boutique. Les gens achètent des choses ici. Ne me dérangez pas !","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tu sais, "+NPChar.name+"Peut-être la prochaine fois.","Bien, j'ai oublié pour une raison quelconque...","Oui, c'est vraiment la troisième fois...","Hm, je ne vais pas...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason --> Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Findcloves" && !CheckAttribute(npchar, "quest.Portugal"))
			{
   				link.l1 = "Écoutez, j'ai besoin de vêtements élégants. Chers, je veux ressembler à un véritable noble. Avez-vous quelque chose de ce genre ?";
				link.l1.go = "Portugal_cloves";
			}
			//<-- Португалец
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "maarten")
			{
				link.l1 = "Un galion nommé 'Admirable' vous a récemment apporté une cargaison de peaux. Vous rappelez-vous de cela ?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		//Jason --> Португалец
		case "Portugal_cloves":
			dialog.text = "Des habits nobles ? Bien sûr, j'ai un ensemble ici : un pantalon, un pourpoint, une chemise de soie et des bottes. Ça coûte 20 000 pesos. Les vêtements sont de très haute qualité, ils sont confortables et ont une allure remarquable, donc je ne prendrai pas moins pour cela.";
			if (int(pchar.money) >= 20000)
			{
				link.l1 = "Super ! Donne-le-moi.";
				link.l1.go = "Portugal_cloves_1";
			}
			link.l2 = "Hm... Je n'ai pas autant d'argent en ce moment.";
			link.l2.go = "Portugal_cloves_nomoney";
		break;
		
		case "Portugal_cloves_nomoney":
			dialog.text = "Alors reviens quand tu auras l'argent.";
			link.l1 = "D'accord. Je reviendrai !";
			link.l1.go = "exit";
		break;
		
		case "Portugal_cloves_1":
			AddMoneyToCharacter(pchar, -20000);
			GiveItem2Character(pchar, "suit_1");
			Log_Info("You've received expensive clothing");
			PlaySound("interface\important_item.wav");
			dialog.text = "Voici pour vous.";
			link.l1 = "Merci !";
			link.l1.go = "exit";
			npchar.quest.Portugal = "true";
			sld = characterFromId("PortugalDoctor");
			sld.dialog.currentnode = "Portugal_doctor_4";
			DelLandQuestMark(characterFromId("Marigo_trader"));
			AddLandQuestMark(characterFromId("PortugalDoctor"), "questmarkmain");
			QuestPointerDelLoc("marigo_town", "reload", "reload6_back");
			QuestPointerToLoc("marigo_town", "reload", "houseF1");
		break;
		//<-- Португалец
		case "guardoftruth":
			dialog.text = "Oui. Il est arrivé à l'heure, a déchargé la marchandise, et je l'ai payée comme nous en étions convenus. Pourquoi demandes-tu cela ?";
			link.l1 = "Le capitaine de ce navire est Gaius Marchais, une vieille connaissance à moi. Je cherche donc à le retrouver. Pourriez-vous me dire ce qu'il a fait ensuite ? Peut-être lui avez-vous fourni des marchandises supplémentaires ou il a mentionné où il comptait se diriger ?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Nothing of that. I didn't offer him any freight; he didn't even ask for it. He didn't share his plans for the future with me. I don't even remember all the details, do you know how many people have come in and out of here since that time? He unloaded and sailed off and that's all I can say about him.";
			link.l1 = "D'accord. Eh bien, merci quand même. Bonne chance !";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "11");
			pchar.questTemp.Guardoftruth = "maarten1";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
