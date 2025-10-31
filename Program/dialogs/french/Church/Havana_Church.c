// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quel genre de questions, "+GetSexPhrase("mon fils","ma fille")+"?","Demandez, je vous écoute..."),"Je vous écoute, parlez maintenant, "+GetSexPhrase("mon fils","ma fille")+"...","Pour la troisième fois, "+GetSexPhrase("mon fils","mafille")+", demandez ce dont vous avez besoin.","Un ecclésiastique a beaucoup de travail et tu me distrais, "+GetSexPhrase("mon fils","ma fille")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Pas en ce moment, padre..."),"Je n'ai rien à dire, mes excuses.","Je demanderai, mais plus tard. Pardonnez-moi, mon père.","Pardonnez-moi, saint père...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana")
			{
				ref sld = characterFromId("Villemstad_Priest");
				link.l1 = "Salutations, père. Père supérieur "+sld.name+" de l'église de Willemstad m'a envoyé. Vous lui avez parlé d'étranges apparitions dans une grotte à Cuba.";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana1")
			{
				link.l1 = "J'ai visité la grotte dans la jungle, mon père.";
				link.l1.go = "caleuche_4";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "caleuche":
			dialog.text = "Dieu merci, il y a prêté attention ! Une fois que les rumeurs sur les morts-vivants ont atteint mes oreilles, j'ai immédiatement informé Son Excellence le Père Vincento, l'inquisiteur de Santiago. Il a promis d'examiner la question, mais jusqu'à présent, aucune action n'a été entreprise ! J'ai bien peur que Son Excellence ait des affaires plus importantes à traiter...";
			link.l1 = "Je vais m'en occuper moi-même. D'ailleurs, toutes ces rumeurs ne sont que les divagations de chasseurs ivres - c'est pourquoi l'Inquisition ne les a pas prises au sérieux. Je vais me rendre dans la jungle pour en être témoin de mes propres yeux.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Je vous assure, mon fils, c'est crucial. L'homme qui m'a parlé des morts-vivants, je lui confie ma vie.";
			link.l1 = "Très bien alors, je me préparerai pour la bataille. Si les créatures impies ont réellement pris racine dans la caverne, je les expurgerai de ce monde.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Va avec la bénédiction du Seigneur, mon fils ! Prends cet amulette sanctifiée. Elle t'aidera dans ta tâche. Va maintenant, détruis les rejetons du mal !";
			link.l1 = "Jusqu'alors, Père "+npchar.name+"Une fois que j'aurai terminé, je reviendrai immédiatement vers vous.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "27");
			pchar.questTemp.Caleuche = "cave";
			Log_Info("You have received a church amulet");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_7"); 
			if (GetCharacterIndex("cavehunter") != -1)
			{
				sld = characterFromId("cavehunter");
				sld.dialog.currentnode = "cavehunter_5";
				LAi_SetGuardianType(sld);
				sld.protector = true;
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				AddLandQuestMark(sld, "questmarkmain");
			}
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload2_back", false);
			pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1 = "location";
			pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1.location = "Cuba_CaveEntrance";
			pchar.quest.Caleuche_cuba_caveentrance.function = "Caleuche_CubaCaveEntrance";
		break;
		
		case "caleuche_4":
			dialog.text = "Qu'as-tu vu, mon fils ? Nos craintes étaient-elles infondées ?";
			link.l1 = "Je crains que non, mon Père "+npchar.name+"La caverne était infestée de morts-vivants, mais avec l'aide de Dieu, j'en suis sorti victorieux. Ils ne gêneront plus personne.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Rendons grâce au Seigneur ! Vous êtes en vérité son glaive châtiant, mon fils ! Permettez-moi de vous exprimer ma plus profonde gratitude au nom de toute la paroisse de La Havane. Veuillez, je vous prie, accepter ces amulettes sanctifiées en signe de reconnaissance. Vous les trouverez sûrement utiles dans vos périlleux voyages.";
			link.l1 = "Merci, Père "+npchar.name+".";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			Log_Info("You have received church amulets");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_3"); 
			GiveItem2Character(pchar, "amulet_9"); 
			GiveItem2Character(pchar, "obereg_7"); 
			GiveItem2Character(pchar, "obereg_11"); 
			dialog.text = "De plus, je m'assurerai que tant les gens du commun que les gentilshommes soient informés de votre acte héroïque et je prierai sans relâche pour vous jour et nuit.";
			link.l1 = "Merci, mon Père. J'ai aussi une autre question à poser.";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Demande, mon fils.";
			link.l1 = "Dis-moi, mon Père "+npchar.name+", un homme du nom de Joachim Merriman est-il arrivé dans votre ville récemment ? Un seigneur d'âge moyen, un Portugais avec une moustache, une barbe impériale et des yeux perçants ?";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "Ni le nom ni la description ne me disent quelque chose, je suis désolé. Qui est cet homme ?";
			link.l1 = "Merriman est un sorcier. L'Inquisition le traque depuis très longtemps. Père "+sld.name+" et je soupçonne que l'apparition des morts-vivants à Cuba est son oeuvre. Il n'y a pas longtemps, il vivait à Willemstad, puis il a soudainement disparu. Peu après, la femme qui l'hébergeait s'est transformée en squelette ambulant.";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Quel cauchemar ! J'informerai immédiatement les inquisiteurs, le Père Vincento lui-même ! Il doit savoir ce qui se passe ici ! Dis-moi, mon fils, penses-tu que les gens qui ont disparu dans la jungle... ?";
			link.l1 = "En effet, je suis presque certain que ces morts-vivants dans la caverne étaient vos anciens citoyens. Je veux traquer ce Portugais à Cuba et le ramener à la raison ! Ce vaurien a réussi à mettre la main sur une vieille relique païenne - un crâne de jade de Yum Cimil. Je crains qu'avec cet artefact et la sorcellerie indienne, Merriman ne cause encore plus de problèmes si personne ne l'arrête bientôt.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "Croyez-vous que les morts-vivants se relèveront encore ?";
			link.l1 = "Presque certainement. Je ne sais pas ce qui le motive, mais sûrement ses aspirations sont loin d'être vertueuses.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = "Puisse le Tout-Puissant nous faire miséricorde ! Cherche-le, mon fils ! Je te permets de prendre toutes les mesures nécessaires contre lui au nom de notre Sainte Église ! J'enverrai immédiatement un messager à Santiago avec un rapport pour le Père Vincento.";
			link.l1 = "Faites donc cela. Adieu, Mon Père "+npchar.name+".";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			DialogExit();
			AddQuestRecord("Caleuche", "29");
			pchar.questTemp.Caleuche = "graveyard";
			AddCharacterMaxHealth(pchar, 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddLandQuestMark(characterFromId("Havana_CemeteryMan"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
