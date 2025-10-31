// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quel genre de questions, "+GetSexPhrase("mon fils","mafille")+"?","Demandez donc, j'écoute..."),"Je vous écoute, parlez maintenant, "+GetSexPhrase("mon fils","ma fille")+"... ","Pour la troisième fois, "+GetSexPhrase("mon fils","ma fille")+", demandez ce dont vous avez besoin.","Un ecclésiastique a beaucoup de travail et vous me distraisez, "+GetSexPhrase("mon fils","ma fille")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Pas pour l'instant, padre..."),"Je n'ai rien à dire, mes excuses.","Je demanderai, mais plus tard. Pardonnez-moi, mon père.","Pardonnez-moi, saint père...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "priest")
			{
				link.l1 = "Excusez-moi, mon père, un des membres du clergé de votre paroisse m'a demandé d'enquêter sur la maison où Joachim Merriman louait une chambre...";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Alors? Y es-tu allé, mon fils?";
			link.l1 = "Je l'ai fait. Mais honnêtement, cela aurait été mieux si je ne l'avais pas fait. J'ai été attaqué par un squelette avec une hache énorme dans la pièce du haut. J'ai réussi à en sortir victorieux, bien que cela n'ait certainement pas été facile.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Mon Seigneur, ayez pitié de nos âmes ! Mes pires craintes se sont réalisées !";
			link.l1 = "Ce n'est pas tout, père. Quand je l'ai finalement abattu, il a poussé un cri aigu et ça sonnait comme une femme. En fouillant les os, j'ai trouvé des bijoux, donc on peut supposer en toute sécurité que c'était la logeuse qui avait disparu.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "(se signe)... Pauvre servante de Dieu, que le Seigneur repose son âme...";
			link.l1 = "Il semble que Merriman soit effectivement un sorcier. Je n'ai aucune idée de comment on peut transformer un homme vivant en une telle abomination.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "Joachim Merriman est un sorcier très redoutable, mon fils. Je l'ai connu en Europe, mais à l'époque, il n'était pas capable de telles choses. Ici, aux Caraïbes, il a réussi à mettre la main sur quelque chose qui lui a donné des pouvoirs surnaturels.";
			link.l1 = "Vous connaissiez Merriman, Père ?";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "That I did. Back then I was just a humble priest in one of Lisbon's parishes. Joachim Merriman was a wealthy nobleman, and at some point he became interested in old manuscripts and scrolls brought by sailors from distant lands. He also began to study alchemy, but after some time he went into seclusion.\nPeople saw flashes of light in his house; sometimes they could also smell something strange. Then they saw him in the cemetery at nights. Once they saw him digging out a fresh corpse and bringing it to his home. And when patience ran out, local father superior contacted the Inquisition.\nWhen the guards breached the door of Merriman's house, Joachim was not there - he had escaped through a secret passage. They found a lab in the basement, and even the seasoned soldiers were shocked and sickened by what they saw. Whole rotting and dismembered bodies, human and animal skeletons, strange things... Fear and hatred for Merriman was so significant that his house was demolished in an instant.\nMerriman disappeared without a trace. The Inquisition began to search for him, sentencing him in his absence to burn at a stake as a dangerous warlock. But they never found him. And now, after all these years, I saw him again on the streets of Willemstad.";
			link.l1 = "Pourquoi n'as-tu pas informé les inquisiteurs ?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Mon fils, ne sais-tu pas que notre église est en désaccord avec l'Inquisition ? Je préférerais éviter Père Vincento et ses brutes.";
			link.l1 = "Je comprends. Mon Père, je crois savoir d'où Merriman tire son pouvoir. Il s'est emparé d'un artefact ancien, un crâne de jade de Yum Cimil, un ancien dieu de la mort vénéré par les Indiens de la tribu Chavin.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Hm, Merriman était connu pour exécuter des rituels sorciers et des expériences sur des cadavres, donc cela pourrait bien être vrai. Je remercie Dieu que cet homme terrible ait quitté Willemstad et que vous ayez détruit les semences diaboliques qu'il a tenté de planter ici. Nous vous sommes grandement redevables, mon fils. Veuillez accepter ces objets sanctifiés en guise de récompense.";
			link.l1 = "Merci, Mon Père";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			Log_Info("You have received church amulets");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_2"); 
			GiveItem2Character(pchar, "amulet_6"); 
			GiveItem2Character(pchar, "amulet_8"); 
			GiveItem2Character(pchar, "amulet_10"); 
			ref sld = characterFromId("Havana_Priest");
			dialog.text = "Mais ce n'était pas la fin de nos ennuis, mon fils. Récemment, j'ai reçu une lettre de "+sld.name+", père supérieur de l'église à La Havane. Il apporte de terribles nouvelles. Dans une grotte, dans la jungle de Cuba, des chasseurs ont vu des abominations effrayantes, des morts-vivants. Et c'est d'autant plus gênant que, récemment, des personnes ont disparu après être entrées dans la jungle.";
			link.l1 = "Hmm... insinues-tu que c'est aussi l'oeuvre de Merriman ?";
			if (CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 30) link.l1.go = "caleuche_8_1";
			else link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			sld = characterFromId("Havana_Priest");
			dialog.text = "Je ne sais pas quoi penser, mon fils. Mais si cette sorcière noire est devenue si puissante, tous les habitants de l'archipel sont en grand danger. Seul Dieu sait ce que ce serviteur du diable pourrait avoir en tête\nJ'espère bien que Père "+sld.name+"était faux, mais quoi qu'il en soit - veuillez aller à La Havane et lui parler. J'ai préparé une licence commerciale pour vous, qui est valable pour un mois. Avec elle, vous pourrez entrer au port de La Havane sans aucune difficulté.";
			link.l1 = "D'accord, Père. Je me rendrai à La Havane.";
			link.l1.go = "caleuche_9";
			npchar.quest.givelicence = true;
		break;
		
		case "caleuche_8_1":
			sld = characterFromId("Havana_Priest");
			dialog.text = "Je ne sais pas quoi penser, mon fils. Mais si ce sorcier noir est devenu si puissant, tous les habitants de l'archipel sont en grand danger. Seul Dieu sait ce que ce serviteur des diables pourrait avoir en tête.\nJ'espère vraiment que Père "+sld.name+" était erroné, mais peu importe - je vous demande de voyager à La Havane et de lui parler.";
			link.l1 = "Bien sûr, Mon Père. Je me rends à La Havane immédiatement.";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Je suis heureux que vous soyez un véritable fils de l'Église. Je prierai pour votre santé et votre bien-être jour et nuit. Allez avec ma bénédiction. Que le Seigneur vous fortifie dans votre lutte contre ces pouvoirs impies.";
			link.l1 = "Merci et adieu, mon père.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			DialogExit();
			AddQuestRecord("Caleuche", "26");
			AddCharacterMaxHealth(pchar, 1);
			if (CheckAttribute(npchar, "quest.givelicence")) GiveNationLicence(HOLLAND, 30);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, HOLLAND, 5);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			pchar.questTemp.Caleuche = "havana";
			Caleuche_PrepareCubaGrot();
			AddLandQuestMark(characterFromId("Havana_Priest"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
