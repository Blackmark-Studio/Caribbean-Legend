// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quelles questions as-tu?","Comment puis-je vous aider, "+GetAddress_Form(NPChar)+"?"),"Tu as essayé de me poser une question il n'y a pas longtemps, "+GetAddress_Form(NPChar)+"...","Pendant toute cette journée, c'est la troisième fois que tu parles d'une question...","Encore des questions, je présume ?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Je n'ai rien à dire pour le moment."),"Oumph, où est passée ma mémoire...","Oui, c'est vraiment la troisième fois...","Non, quelles questions?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Jason, Бремя гасконца
			if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && int(environment.time) > 5.0 && int(environment.time) < 19.0)
			{
				link.l1 = "Monsieur, je cherche du travail. Avez-vous des emplois ?";
                link.l1.go = "Sharlie_rum";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
			{
				link.l1 = "J'ai rempli ta mission. La chaloupe avec le rhum a été livrée à la baie de Le Francois et remise à tes gens.";
                link.l1.go = "Sharlie_rum_5";
			}	
			//<-- Бремя гасконца */
			
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToMartinique" && !CheckAttribute(npchar, "quest.Portugal"))
			{
				link.l1 = "J'ai besoin de louer une de vos chambres pour deux ou trois jours. J'ai un homme à bord qui est blessé. Il a besoin de repos et de se remettre.";
				link.l1.go = "Portugal";
			}
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernorEnd")
			{
				link.l1 = "Dis-moi. Mon ami pour qui j'ai loué une chambre, est-il parti ? Il m'a promis de m'attendre, mais la chambre est vide.";
				link.l1.go = "Portugal_2";
			}
			//Португалец
			// Jason Долго и счастливо
			if (!CheckAttribute(npchar, "quest.LongHappy") && CheckAttribute(PChar, "questTemp.LongHappy.MarryRum") && LongHappy_CheckTavernGoods())
			{
				link.l1 = "Je vais organiser une fête pour mes hommes. Je suppose que vous êtes déjà au courant ?";
				link.l1.go = "LH_tavern_SP";
			}
			if (CheckAttribute(npchar, "quest.LongHappy.Nomoney") && LongHappy_CheckTavernGoods() && int(Pchar.money) >= 100000+int(pchar.questTemp.LongHappy.MarryMoney))
			{
				link.l1 = "J'ai apporté tout ce qu'il fallait pour notre célébration.";
				link.l1.go = "LH_tavern_SP_3";
			}
		break;
		
		//--> Jason, Бремя гасконца
		case "Sharlie_rum":
			DelLandQuestMark(npchar);
			dialog.text = "Une tâche ? Hm... Tu as l'air d'avoir un peu de cervelle, garçon. J'ai peut-être quelque chose pour toi.\nCe travail peut sembler facile, mais il nécessite de la responsabilité et de l'intelligence. Je ne peux pas faire confiance à ces idiots pour s'occuper des affaires, ils vont sûrement tout gâcher...";
			link.l1 = "Ecoute, peux-tu simplement me dire ce que diable tu veux me confier ? Je te jure, je ne te laisserai pas tomber ou du moins je ferai de mon mieux.";
			link.l1.go = "Sharlie_rum_1";
		break;
		
		case "Sharlie_rum_1":
			switch(rand(4))
			{
				case 0:
					pchar.questTemp.Sharlie.Rum.Pass = "Old Thomas has grown tired of waiting for the beer";
				break;
				case 1:
					pchar.questTemp.Sharlie.Rum.Pass = "The boards and the oakum will be here in the morning";
				break;
				case 2:
					pchar.questTemp.Sharlie.Rum.Pass = "Don't wait for the south wind";
				break;
				case 3:
					pchar.questTemp.Sharlie.Rum.Pass = "The bay is ready for disembarkation";
				break;
				case 4:
					pchar.questTemp.Sharlie.Rum.Pass = "The camels are going north";
				break;
			}
			dialog.text = "Bien. J'ai besoin de quelqu'un pour livrer plusieurs caisses de rhum de la Jamaïque de qualité à ma taverne. Voilà le problème, les droits d'importation rognent mes marges et mes meilleurs clients ont soif, alors nous devons être malins pour éviter les douaniers. Le lougre 'Fantôme' arrivera au large de la Martinique ce soir\nIls jetteront l'ancre non loin de la baie de Lamantin. Vous devez trouver ce navire et monter à bord. Je vous fournirai un canot et cinq matelots, ils suivront vos ordres\nUne fois à bord, un homme vous approchera. Vous devrez lui dire un mot de passe : '"+pchar.questTemp.Sharlie.Rum.Pass+"'\nLa réponse sera 'Pourquoi ne pas prendre un rhum, matelot ?'. Tu n'auras qu'une seule tentative, alors écris-la et ne fais pas d'erreur sinon l'affaire est annulée. C'est pour ça que je ne peux pas la confier à ces crétins sans cervelle qui vogueront avec toi. Répète le mot de passe.";
			link.l1 = "'"+pchar.questTemp.Sharlie.Rum.Pass+". ";
			link.l1.go = "Sharlie_rum_2";
		break;
		
		case "Sharlie_rum_2":
			dialog.text = "Parfait. Répétez-le encore quelques fois, ou mieux encore, écrivez-le quelque part. Après avoir mentionné le mot de passe au capitaine du lougre, les caisses avec des bouteilles de rhum seront chargées sur la chaloupe, que vous devrez ensuite naviguer jusqu'à la baie de la colonie pirate Le Francois - vous serez accueilli là-bas.\nC'est toute la tâche. Vous pouvez rejoindre Saint Pierre à pied depuis la baie de Le Francois - la chaloupe restera dans la baie. Je paierai cinq mille pièces de huit une fois que ce sera fait.";
			link.l1 = "La contrebande semble à la fois excitante et lucrative. Je ferai ce que vous m'avez dit de faire. Où est la chaloupe ?";
			link.l1.go = "Sharlie_rum_3";
			link.l2 = "Alors, tu proposes que je me lance dans la contrebande ? Hm... Tu sais, je ne peux pas risquer mon nom. Tu devras m'excuser, faisons comme si je n'avais rien entendu.";
			link.l2.go = "Sharlie_rum_exit";
		break;
		
		case "Sharlie_rum_exit":
			dialog.text = "Comme vous le souhaitez, monsieur. Je n'ai pas d'autres travaux.";
			link.l1 = "Je vois. Alors tout le meilleur, "+npchar.name+".";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
			SetCurrentTime(23, 0);
			Sharlie_removeLocks("");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload4_back");
		break;
		
		case "Sharlie_rum_3":
			dialog.text = "La chaloupe sera au quai à sept heures du soir. L'équipage de la chaloupe est habile, donc vous devriez atteindre le lougre rapidement. Toute la tâche ne devrait pas prendre plus de quatre heures - je suis sûr que vous serez de retour à Saint Pierre à onze heures du soir. Prenez cette longue-vue, c'est un bout de ferraille mais c'est mieux que rien. La plage de Lamanten est située à la partie nord de l'île, donc en quittant le port, gardez le cap plein nord. Bonne chance !";
			link.l1 = "Très bien, compris. À bientôt, "+npchar.name+" !";
			link.l1.go = "Sharlie_rum_4";
		break;
		
		case "Sharlie_rum_4":
			DialogExit();
			AddQuestRecord("SharlieB", "1");
			AddQuestUserData("SharlieB", "sPassword", pchar.questTemp.Sharlie.Rum.Pass);
			GiveItem2Character(pchar, "spyglass1"); 
			Log_Info("You've received a spyglass");
			PlaySound("interface\important_item.wav");
			if(CheckAttribute(pchar, "questTemp.Sharlie.FastStart"))
			{
				GiveItem2Character(pchar, "map_martiniqua");
				Log_Info("You have received a map of Martinique");
				RefreshEquippedMaps(GetMainCharacter());
			}
			/* pchar.quest.Sharlie_rum.win_condition.l1 = "location";
			pchar.quest.Sharlie_rum.win_condition.l1.location = "Fortfrance_town"; */
			//pchar.quest.Sharlie_rum.win_condition.l1.locator_group = "rld";
			//pchar.quest.Sharlie_rum.win_condition.l1.locator = "loc0";
			pchar.quest.Sharlie_rum.win_condition.l1 = "HardHour";
			pchar.quest.Sharlie_rum.win_condition.l1.hour = 19.00;
			pchar.quest.Sharlie_rum.function = "Rum_CreateBarkas";
			SetFunctionTimerCondition("Rum_CreateBarkasOver", 0, 0, 1, false);
			pchar.questTemp.Sharlie.Rum = "true";
			npchar.quest.Rum = "true";
			NewGameTip("Open your inventory (F1) and equip the spyglass.");
			pchar.quest.NgtBarkas.win_condition.l1 = "location";
			pchar.quest.NgtBarkas.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.NgtBarkas.win_condition.l2 = "HardHour";
			pchar.quest.NgtBarkas.win_condition.l2.hour = 19.00;
			pchar.quest.NgtBarkas.function = "NgtBarkas";
			AddTimeToCurrent(1,30);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload4_back");
			QuestPointerToLoc("fortfrance_town", "reload", "reload1_back");
		break;
		
		case "Sharlie_rum_5":
			dialog.text = "Merveilleux ! Je savais que je pouvais compter sur vous. Cela a-t-il été difficile ?";
			link.l1 = "Eh bien, cela dépend de la façon dont vous définissez le mot dur...";
			link.l1.go = "Sharlie_rum_6";
		break;
		
		case "Sharlie_rum_6":
			dialog.text = "Eh bien, voici votre récompense : cinq mille pesos. Vous pouvez garder la longue-vue. Et aussi, un autre petit cadeau, s'il vous plaît, prenez ces trois bouteilles de rhum. Une fois que vous l'aurez goûté, vous comprendrez pourquoi il y a une telle demande pour cela.";
			link.l1 = "Merci ! C'était un plaisir de travailler avec vous ! À plus tard !";
			link.l1.go = "Sharlie_rum_7";
		break;
		
		case "Sharlie_rum_7":
			DialogExit();
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "potionrum", 3);
			AddQuestRecord("SharlieB", "5");
			CloseQuestHeader("SharlieB");
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload4_back");
			DelLandQuestMark(npchar);
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		//<-- Бремя гасконца
		
		//Португалец
		case "Portugal":
			dialog.text = "Aucun problème, j'ai une chambre. Pour 50 pesos, elle est à vous pour trois jours.";
			if (int(pchar.money) >= 50)
			{
				link.l1 = "Voilà.";
				link.l1.go = "Portugal_1";
			}
			else
			{
				link.l1 = "Je vais prendre l'argent chez le trésorier et je reviendrai.";
				link.l1.go = "exit";
			}
		break;
		
		case "Portugal_1":
			ref sld;
			DialogExit();
			AddMoneyToCharacter(pchar, -50);
			npchar.quest.Portugal = "true";
			LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", false);
			pchar.quest.Portugal_Ill3.over = "yes";
			LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("Fortfrance_town", "gate_back", true);//закрыть выходы из города
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto3");
			sld = characterFromId("PortugalDoctor");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto1");
			pchar.quest.Portugal_tavernroom.win_condition.l1 = "location";
			pchar.quest.Portugal_tavernroom.win_condition.l1.location = "FortFrance_tavern_upstairs";
			pchar.quest.Portugal_tavernroom.function = "PortugalInTavernRoom";
		break;
		
		case "Portugal_2":
			dialog.text = "Je ne dirais pas qu'il s'est levé et a quitté la pièce tout seul, monsieur. Des gens sont passés ici hier. L'un d'eux était un grand homme mince borgne - un bandit évident à en juger par son apparence, et un autre homme qui zozotait, il avait l'air d'un Castillan. J'étais juste surpris, mais ce zozoteur m'a regardé... comme un pou avant qu'on ne l'écrase. Et donc, ils ont demandé après votre ami... et je leur ai dit. Que pouvais-je faire d'autre ?";
			link.l1 = "Je sais, "+npchar.name+", tu n'es pas un héros, c'est vrai. Qu'as-tu vu d'autre ? Où sont-ils allés ?";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "C'est tout... attends, non! Attends, l'homme borgne a dit quelque chose à propos d'une charrette. Je suppose qu'ils ont pris une charrette et ont traîné votre ami de l'autre côté de l'île. C'est tout monsieur, je le jure... J'appellerais la garde, mais ce zozoteur m'a dit que j'avais une belle épouse avant de partir... Tu vois? S'ils découvrent que je t'ai raconté tout ça, ils vont...";
			if (pchar.money >= 1000)
			{
				link.l1 = "N'aie pas peur, ils n'entendront rien de moi à part des balles. Tu m'as vraiment aidé, merci. Tiens, prends 1000 pesos en récompense.";
				link.l1.go = "Portugal_4";
			}
			link.l2 = "Ce n'est pas grand-chose, mais merci quand même. La prochaine fois, appelle la garde et ne sois pas si peureux.";
			link.l2.go = "Portugal_5";
		break;
		
		case "Portugal_4":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Merci, monsieur. Je peux vous donner ma parole que votre ami est presque rétabli. Il marchait au moins par lui-même. Et l'autre homme, ce Hollandais silencieux, il est entré de l'extérieur à ce moment-là, a vu tout ce désordre et a sauté dehors, il a simplement disparu après.";
			link.l1 = "Je dirais qu'il est déjà parti sur le premier navire qu'il a pu prendre. Merci pour l'information, il est temps pour moi de partir.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_5":
			dialog.text = "Tout homme ne peut être un héros avec son épée dégainée, capitaine.";
			link.l1 = "Eh bien... c'est le choix de l'homme.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			DialogExit();
			sld = characterFromId("Avendel");
			sld.dialog.currentnode = "Avendel_seapatrol_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		//Португалец
		
		// Jason Долго и счастливо
		case "LH_tavern_SP":
			npchar.quest.LongHappy = "true";
			dialog.text = "Oui, votre assistante est passée, mais je lui ai dit et je vais vous répéter - je me suis habitué aux foules de marins ivres, mais je sais comment se passent vos fêtes. Ce qu'il restera ressemblera à Anvers après le passage des tercios espagnols. Je serai heureux si les murs tiennent encore debout. Donc, si vous voulez que la populace se bagarre, j'aurai besoin d'un acompte non remboursable au-delà de ce que vous avez déjà apporté. En cas de conséquences, pour ainsi dire.";
			link.l1 = "Espèce de renard rusé ! Moi-même, j'ai bu avec des vieux loups de mer pendant de nombreuses années, j'ai fréquenté divers... établissements, et je sais que pour l'argent que j'ai apporté, nous pourrions reconstruire votre taverne de fond en comble ! Tu saisis l'occasion, hein ? Très bien, j'ai un mariage, et je n'ai pas l'humeur à me tracasser avec de telles broutilles - combien veux-tu ?";
			link.l1.go = "LH_tavern_SP_1";
		break;
		
		case "LH_tavern_SP_1":
			dialog.text = "Encore 100 000 pièces de huit devraient suffire et ne t'inquiète pas - je ferai tout de la meilleure manière possible. Tes gars se souviendront de cette fête pendant longtemps, souviens-toi de mes paroles !";
			if (int(Pchar.money) >= 100000+int(pchar.questTemp.LongHappy.MarryMoney))
			{
				link.l1 = "Il faut vraiment faire un effort - c'est une occasion spéciale, vous comprenez. Et oui, après la célébration, ne venez pas vous plaindre, même si votre taverne brûle.";
				link.l1.go = "LH_tavern_SP_4";
			}
			else
			{
				link.l1 = "On dirait déjà que j'organise un mariage royal ! Attends, je reviendrai bientôt.";
				link.l1.go = "LH_tavern_SP_2";
			}
		break;
		
		case "LH_tavern_SP_2":
			DialogExit();
			npchar.quest.LongHappy.Nomoney = "true";
		break;
		
		case "LH_tavern_SP_3":
			dialog.text = "Tes gars se souviendront de cette fête pendant longtemps, souviens-toi de mes paroles !";
			link.l1 = "Tu dois vraiment faire un effort - c'est une occasion spéciale, tu comprends. Ne viens pas pleurer chez moi si mes gars brûlent accidentellement ta taverne.";
			link.l1.go = "LH_tavern_SP_4";
		break;
		
		case "LH_tavern_SP_4":
			DialogExit();
			RemoveCharacterGoods(pchar, GOOD_RUM, int(pchar.questTemp.LongHappy.MarryRum));
			AddMoneyToCharacter(pchar, -int(pchar.questTemp.LongHappy.MarryMoney));
			AddMoneyToCharacter(pchar, -100000);
			DeleteAttribute(npchar, "quest.LongHappy.Nomoney");
			pchar.questTemp.LongHappy.DrinkReady = "true";
			pchar.questTemp.LongHappy.MarrySP = "true";
			DeleteAttribute(pchar, "questTemp.LongHappy.MarryMoney");
			DeleteAttribute(pchar, "questTemp.LongHappy.MarryRum");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
