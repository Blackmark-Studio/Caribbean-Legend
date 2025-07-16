// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Che tipo di domande, "+GetSexPhrase("mio figlio","mia figlia")+"?","Fai pure, ti sto ascoltando..."),"Sto ascoltando, parla ora, "+GetSexPhrase("mio figlio","mia figlia")+"...","Per la terza volta, "+GetSexPhrase("mio figlio","mia figlia")+", chiedi ciò di cui hai bisogno.","Un religioso ha molto lavoro e tu mi stai distrarrendo, "+GetSexPhrase("mio figlio","mia figlia")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non in questo momento, padre..."),"Non ho nulla da dire, mi scuso.","Chiederò, ma più tardi. Perdonami, padre.","Perdonatemi, santo padre...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana")
			{
				ref sld = characterFromId("Villemstad_Priest");
				link.l1 = "Saluti padre. Padre superiore "+sld.name+" della chiesa di Willemstad mi ha mandato. Gli hai parlato di strane apparizioni in una grotta a Cuba.";
				link.l1.go = "caleuche";
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana1")
			{
				link.l1 = "Ho visitato la grotta nella giungla, padre.";
				link.l1.go = "caleuche_4";
			}
		break;
		
		case "caleuche":
			dialog.text = "Grazie a Dio che ha prestato attenzione! Non appena i pettegolezzi sui morti viventi sono giunti alle mie orecchie, ho immediatamente avvertito Sua Reverenza Padre Vincento, l'inquisitore di Santiago. Ha promesso di indagare, ma finora non è stata intrapresa alcuna azione! Temo che Sua Reverenza abbia questioni più importanti a cui attendere...";
			link.l1 = "Me ne occuperò personalmente. Dopotutto, tutti questi pettegolezzi non sono altro che i vaneggiamenti di cacciatori ubriachi - ecco perché l'Inquisizione non li ha presi sul serio. Mi dirigerò nella giungla per vederlo con i miei occhi.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Ti assicuro, mio figlio, è fondamentale. L'uomo che mi ha parlato dei morti che camminano, confido in lui con la mia vita.";
			link.l1 = "Molto bene, allora mi preparerò per la battaglia. Se le creature impie hanno davvero preso piede nella caverna, le purgherò da questo mondo.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Vai con la benedizione del Signore, mio figlio! Ecco, prendi questo amuleto santificato. Ti aiuterà nel tuo compito. Vai ora, distruggi le progenie del male!";
			link.l1 = "Fino ad allora, Padre "+npchar.name+". Una volta finito, tornerò da te immediatamente.";
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
			}
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload2_back", false);
			pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1 = "location";
			pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1.location = "Cuba_CaveEntrance";
			pchar.quest.Caleuche_cuba_caveentrance.function = "Caleuche_CubaCaveEntrance";
		break;
		
		case "caleuche_4":
			dialog.text = "Cosa hai visto, mio figlio? Erano infondate le nostre paure?";
			link.l1 = "Mi dispiace, Padre "+npchar.name+". La caverna era piena di non morti, ma con l'aiuto di Dio sono uscito vittorioso. Non daranno più fastidio a nessuno.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Lodate il Signore! Tu sei davvero la sua spada castigatrice, figlio mio! Permettimi di esprimere la mia più profonda gratitudine a nome dell'intera parrocchia dell'Avana. Ti prego, accetta questi amuleti santificati come segno di gratitudine. Sicuramente li troverai utili nei tuoi pericolosi viaggi.";
			link.l1 = "Grazie, Padre "+npchar.name+".";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			Log_Info("You have received church amulets");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_3"); 
			GiveItem2Character(pchar, "amulet_9"); 
			GiveItem2Character(pchar, "obereg_7"); 
			GiveItem2Character(pchar, "obereg_11"); 
			dialog.text = "Inoltre mi assicurerò che sia il popolo che i nobili sappiano della tua eroica impresa e pregherò per te incessantemente giorno e notte.";
			link.l1 = "Grazie, Padre. Ho anche un'altra domanda da fare.";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Chiedi, mio figlio.";
			link.l1 = "Dimmi, Padre "+npchar.name+", è arrivato di recente nella vostra città un uomo di nome Joachim Merriman? Un signore di mezza età, un portoghese con baffi, barba imperiale e occhi penetranti?";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "Né il nome né la descrizione mi dicono nulla, mi dispiace. Chi è quest'uomo?";
			link.l1 = "Merriman è un stregone. L'Inquisizione lo sta cacciando da molto tempo. Padre "+sld.name+" e sospetto che l'emergere dei morti viventi a Cuba sia opera sua. Non molto tempo fa viveva a Willemstad, poi è sparito all'improvviso. Poco dopo, la donna che lo ospitava si è trasformata in uno scheletro ambulante.";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Che incubo! Informerò immediatamente gli inquisitori, Padre Vincento stesso! Deve sapere cosa sta succedendo qui! Dimmi, mio figlio, pensi che le persone scomparse nella giungla...?";
			link.l1 = "Infatti, sono quasi certo che quei morti viventi nella caverna fossero i tuoi ex cittadini. Voglio cercare questo portoghese a Cuba e metterlo in riga! Quel mascalzone è riuscito a mettere le mani su un antico reliquiario pagano - un teschio di giada di Yum Cimil. Temo che con l'artefatto e la stregoneria indiana, Merriman causerà ancora più guai se nessuno lo ferma presto.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "Credi che i non morti risorgeranno?";
			link.l1 = "Quasi certamente. Non sono sicuro di cosa lo spinga, ma sicuramente le sue aspirazioni sono lontane dall'essere virtuose.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = "Che l'Onnipotente abbia pietà di noi! Cercalo, mio figlio! Ti permetto di prendere qualsiasi misura contro di lui nel nome della nostra Santa Chiesa! Invierò immediatamente un messaggero a Santiago con un rapporto per Padre Vincento.";
			link.l1 = "Lo fai tu. Addio, Padre "+npchar.name+".";
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
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
