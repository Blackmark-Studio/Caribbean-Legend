// boal 25/04/04 общий диалог солдат
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	int DeceptionChance  = 0;
	int DeceptionPenalty  = 0;
	if(CheckAttribute(pchar,"StealtDeceptionPenalty")) DeceptionPenalty = sti(pchar.StealtDeceptionPenalty);
	
	DeceptionChance = sti(GetSummonSkillFromName(pchar, SKILL_SNEAK)*100/110);
	if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE) 
	{
		DeceptionChance = sti(GetSummonSkillFromName(pchar, SKILL_SNEAK)*100/310);
		if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	}
	if(sti(pchar.reputation.fame) < 41 && CheckCharacterPerk(pchar, "Trustworthy"))
	{
		DeceptionChance = 100;
		if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	}
	if(DeceptionChance > 90) DeceptionChance = 90;
	// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
    /* // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Soldier\" + NPChar.City + "_Soldier.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <-- */
    int iTest, iTemp;
	string sTemp;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			sTemp = npchar.location;
			if (findsubstr(sTemp, "_townhall" , 0) != -1) AddDialogExitQuest("MainHeroFightModeOff");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":			
            NextDiag.TempNode = "First time";
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				// заглушка на пирата
				if (sti(pchar.nation) == PIRATE)
				{
    				dialog.text = RandPhraseSimple("Piraten in der Stadt?! Kann es nicht glauben... Verhaften "+GetSexPhrase("ihn","ihr")+"!!","Das ist ein Pirat! Ergreifen "+GetSexPhrase("ihn","sie")+"!!!");
					link.l1 = RandPhraseSimple("Ich bin ein Pirat, na und?","Heh, du kannst es ja versuchen...");
					link.l1.go = "fight"; 
					break;
				}
				else
				{
					if (DeceptionChance > (10+rand(150)+rand(150)))
					{
						dialog.text = RandPhraseSimple("Wer bist du und was machst du hier?","Halt! Wer bist du und mit welchem Recht versuchst du, die Stadt zu betreten?");
						link.l2 = "Ich habe den Anker in der Nähe abgeworfen "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" unter der Flagge von "+NationNameGenitive(sti(npchar.nation))+". Was verstehst du nicht? (Wahrscheinlichkeit der Täuschung "+DeceptionChance+"%%)";
						link.l1.go = "NotPegYou";
					}
					else
					{
						dialog.text = RandPhraseSimple("Ein Spion! Übergebt eure Waffe und folgt mir!","Ein Feindagent! Ergreift ihn "+GetSexPhrase("ihn","sie")+"!");
						link.l1 = RandPhraseSimple("Halt den Mund, Weichei!","Fick dich!");
						link.l1.go = "fight"; 
					}
				}
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					// грамота Винсенто
					if(CheckAttribute(pchar, "questTemp.Guardoftruth") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "santiago")
					{
						dialog.text = RandPhraseSimple("Wer bist du und was machst du hier?","Halt! Wer bist du und mit welchem Recht versuchst du, die Stadt zu betreten?");
						link.l1 = "Schau dir dieses Papier an, Soldat. Ich bin hier mit Erlaubnis des Inquisitors, Vater Vincento.";
						link.l1.go = "vincento"; 
						break;
					}
					if(CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "portspein")
					{
						dialog.text = RandPhraseSimple("Wer bist du und was machst du hier?","Halt, wer bist du und mit welchem Recht versuchst du, die Stadt zu betreten?");
						link.l1 = "Schau dir dieses Papier an, Soldat. Ich bin hier mit Erlaubnis des Inquisitors, Vater Vincento.";
						link.l1.go = "vincento"; 
						break;
					}
					if (PChar.location == "Maracaibo_Plantation")
					{
						dialog.text = LinkRandPhrase("Benehmt euch und belästigt die Sklaven nicht.","Mach hin, geh weiter!","Ach, du bist es. Geh nur weiter, wir wurden bereits über dich informiert.");
						link.l1 = "...";
						link.l1.go = "exit";
						break;
					}
					dialog.text = RandPhraseSimple("Wer bist du und was machst du hier?","Halt! Wer bist du und mit welchem Recht versuchst du, in die Stadt einzudringen?");
					//==> по лицензии
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Offizier, ich habe "+GetRusNameNationLicence(HOLLAND)+", also bin ich hier auf rechtlichem Boden. Hier, bitte schau mal...";
						link.l1.go = "LicenceOk";
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l2 = "Siehst du nicht die Flagge von "+NationNameGenitive(sti(pchar.nation))+"auf dem Mast meines Schiffes?! (Wahrscheinlichkeit der Täuschung "+DeceptionChance+"%%)";
						}
						else //если причалил не в городе
						{
							link.l2 = "Ich warf den Anker nahe "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" unter der Flagge von "+NationNameGenitive(sti(pchar.nation))+". Was verstehst du nicht? (Wahrscheinlichkeit der Täuschung "+DeceptionChance+"%%)";
						}
						if (DeceptionChance < (10+rand(50)+rand(50)))
						{
							link.l2.go = "PegYou";
						}
						else
						{
							link.l2.go = "NotPegYou";
						}
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (sti(pchar.nation) == PIRATE)
						{
    						dialog.text = RandPhraseSimple("Piraten in der Stadt?! Kann es nicht glauben... Ergreift ihn!","Das ist ein Pirat! Ergreift ihn!");
							link.l1 = RandPhraseSimple("Ja, ich bin ein Pirat - und jetzt?","Heh, fang mich, wenn du kannst...");
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = "Siehst du die Flagge nicht "+NationNameGenitive(sti(pchar.nation))+" auf meinem Schiff?! (Wahrscheinlichkeit der Täuschung "+DeceptionChance+"%%)";
						}
						else //если причалил не в городе
						{
							link.l1 = "Ich habe den Anker in der Nähe fallen gelassen "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" unter der Flagge "+NationNameGenitive(sti(pchar.nation))+". Was verstehst du nicht? (Wahrscheinlichkeit der Täuschung "+DeceptionChance+"%%)";
						}
						if (DeceptionChance < (10+rand(50)+rand(50)))
						{
							link.l1.go = "PegYou";
						}
						else
						{
							link.l1.go = "NotPegYou";
						}
					}
				}
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn) == true) // наш горожанин
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = "Oh, Kapitän, wir hatten eine so großartige Zeit mit Ihnen auf See! So viele Schiffe, die wir unter Ihrem Kommando gemeinsam versenkt haben! Und hier...";
									link.l1 = "Und hier, mein Freund, kannst du deine Augen an bezaubernden Damen weiden, die du auf See nicht sehen wirst.";
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = "Kapitän, was haben wir getan, um das zu verdienen?! Wir sind doch keine Landratten, oder?";
									link.l1 = "Ruhe, Matrose! Dein Posten ist sehr wichtig und ehrenvoll, also hör auf zu jammern.";
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = "Was geht auf See vor, Kapitän? Werden wir es jemals wieder sehen?";
									link.l1 = "Aber natürlich, Seemann! Sobald du von der Pflicht befreit bist, kannst du zum Pier gehen und das Meer so viel genießen, wie du möchtest.";
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = "Ich möchte mich beschweren, Kapitän: Jeder von uns vermisst das Meer. Wir haben alle vollkommen genug von dieser Landdienstpflicht!";
									link.l1 = "Ich habe genug von diesem Gejammer! Du hast hier auch genug Rum! Dienen Sie dort, wo Sie vom Kapitän platziert wurden, oder sonst wird jemand als Beispiel für andere gehängt.";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "Ich sage Ihnen im Vertrauen, Kapitän, der neue Gouverneur ist ein Bestechungsempfänger und Unterschlagungstäter. Aber das geht mich wirklich nichts an...";
									link.l1 = "Genau, Freibeuter. Deine Aufgabe ist es, an deinem Posten zu stehen und für Ordnung zu sorgen. Und den Gouverneur am Rah zu hängen ist meine Aufgabe. Gute Arbeit!";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "Danke, dass Sie uns nicht vergessen haben, Kapitän! Wir würden Ihnen durch Feuer und Wasser folgen!";
									link.l1 = "Ich kenne deine Sorte, Gauner! Alles, was ihr wirklich liebt, ist Gold. Heute Abend ist eine Party in der Taverne, Getränke gehen auf mich. Vergiss nicht zu kommen.";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "Heh, Kapitän! Denk mal darüber nach, kann ein Korsar wirklich ein Hüter der Ordnung sein?! Es ist schon so lange her, dass wir das letzte Mal im echten Geschäft waren!";
									link.l1 = "Keine Zeit zum Entspannen, Korsar! Feindliche Flotten durchkämmen die Gewässer um unsere Inseln, und wir müssen jederzeit bereit für ein Blutbad sein.";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "Kapitän, ich habe gehört, dass die Krone eine weitere Staffel auf uns angesetzt hat?";
									link.l1 = "Natürlich, Korsar. Solange wir leben, wird es für uns keinen Frieden geben. Und selbst in der Hölle werden wir gegen Teufel kämpfen!";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "Yo-ho-ho! Verdammt, das war ein wirklich starker Schnaps gestern, Kapitän! Schade, dass du nicht da warst.";
									link.l1 = "Keine große Sache, ich werde es wiedergutmachen. Und ich beneide euch nicht, Leute.";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "Ich sage Ihnen im Vertrauen, Kapitän, weil Sie uns immer gut behandelt haben, wir hatten gestern eine gute Zeit mit einem wirklich netten Küken...";
									link.l1 = "Heh, Freibeuter, ein Galgen ist etwas, was du wirklich brauchst!";
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = "Käpt'n! Bitte, erlöse mich von dieser verfluchten Pflicht! Ich kann einfach nicht mehr die Rolle eines Hüters der Ordnung spielen.";
									link.l1 = "Nachtwache auf einem Schiff ist auch nicht einfach. Freund, Pflicht ist Pflicht, was auch immer und wo auch immer sie ist.";
									link.l1.go = "exit";
								break;
							}
							// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
							/* link.l2 = RandPhraseSimple("Es gibt eine wichtige Angelegenheit!","Ich habe eine Angelegenheit mit dir.");
							link.l2.go = "quests";//(перессылка в файл города) */
							break;
						}
						else
						{ // пираты, не наши
							if (sti(pchar.GenQuest.Piratekill) > 20)
							{
								dialog.text = RandPhraseSimple("Achtung! Bewaffneter kranker Wahnsinniger ist hier!","Zu den Waffen, zu den Waffen! Ein verrückter Bastard ist hier!");
								link.l1 = RandPhraseSimple("Hä? Was?","Äh, warum tust du das?");
								link.l1.go = "pirate_fight";
							}
							else
							{
							    /* dialog.text = LinkRandPhrase(RandPhraseSimple("Haben Sie ein Anliegen bei mir, Kapitän?","Ich bin hier geschäftlich unterwegs, wenn Sie etwas brauchen - fragen Sie, zögern Sie nicht."),RandPhraseSimple("Kapitän, ich bin sehr beschäftigt, also suchen Sie nach anderen Gesprächspartnern.","Etwas stimmt nicht, Kapitän? Wenn es keine Fragen gibt, darf ich dann gehen?"),"Geben Sie den Weg frei, Kapitän, ich habe es eilig.");
							link.l1 = LinkRandPhrase("Entschuldigung, Freund, ich "+GetSexPhrase("Verlaufen","hat sich verlaufen")+" ","Also, kümmere dich um deine eigenen Angelegenheiten.","Nein, nichts.");
							link.l1.go = "exit";
							link.l2 = LinkRandPhrase(RandPhraseSimple("Ich habe ein paar Fragen an dich.","Ich habe ein Anliegen an dich."),RandPhraseSimple("Ich sehe, du hast es eilig. Eine Frage und du bist frei.","Ich "+GetSexPhrase("wollte","wollte")+" etwas fragen."),"Deine Angelegenheiten können warten. Ich wollte das fragen "+GetSexPhrase("wollte","wollte")+".");
							    link.l2.go = "quests";//(перессылка в файл города) */
								
								//Экку Korsar - что-то они больно вежливые для пиратов были...
								dialog.text = RandPhraseSimple("Was willst du? Geh vorbei.","Hör auf, den Weg zu blockieren, weiche zurück.");
					            link.l1 = RandPhraseSimple("Weißt du was? Bell nicht!","Dämpfe deinen Eifer. Ich werde ihn nicht schnell abkühlen!");
					            link.l1.go = "exit";
						    	/* link.l2 = LinkRandPhrase(RandPhraseSimple("Ich habe ein paar Fragen an dich.","Ich habe ein Anliegen an dich."),RandPhraseSimple("Sehe, dass du es eilig hast. Eine Frage und du bist frei.","Ich "+GetSexPhrase("wollte","wollte")+" etwas fragen."),"Deine Angelegenheiten können warten. Ich möchte folgendes fragen "+GetSexPhrase("wollte","wollte")+".");
							link.l2.go = "quests";//(перессылка в файл города) */
							}
							break;
						}
					}
					else
					{ //если негодяй, имеющий НЗГ к дружественной или нейтральной нации
						if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
						{
							dialog.text = RandPhraseSimple("Nur schau  "+GetSexPhrase("auf diesen Schurken! Er wagte es, sein Gesicht zu zeigen","auf diesen Schurken! Sie wagte es, ihr Gesicht zu zeigen")+" in "+XI_ConvertString("Colony"+npchar.city)+". Ergreife "+GetSexPhrase("ihn","sie")+"!!!","Ha, ich habe dich erkannt, "+GetSexPhrase("Schurke","Schurke")+"! Ergreifen "+GetSexPhrase("ihn","sie")+"!!!");
							link.l1 = RandPhraseSimple("Argh!..","Nun, du hast danach gefragt...");
							link.l1.go = "fight";
							break;						
						}
					}

					// --> девица в джунглях
					if(rand(2) == 1 && CheckAttribute(pchar,"GenQuest.EncGirl") && CheckAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers"))
					{
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 1)	
						{
							dialog.text = "Oh, schau mal wer da ist! Dame "+pchar.GenQuest.EncGirl.name+" Sie hat uns mit ihrer Anwesenheit geehrt! Ich frage mich, wie Sie es gewagt haben? Wir haben nach Ihnen gesucht! Bitte gehen Sie zum Kerker - Ihre Zelle ist bereit und wartet auf Sie. ";
							link.l1 = "Welchen absoluten Unsinn redest du!? Ich und mein "+GetSexPhrase("Kavalier","Gefährte")+" machten einen Spaziergang im Dschungel, pflückten Blumen. Lassen Sie mich in Ruhe! Wo sind die Manieren dieser Martinets?! Sobald sie ein attraktives Mädchen sehen, fangen sie an, sie zu nerven! "+GetSexPhrase("Meine Liebe, bitte sag diesen Dummköpfen, sie sollen verschwinden und eine ehrliche Frau in Ruhe lassen!","Liebling, bitte sag diesen Dummköpfen...")+"!";
							link.l1.go = "GirlEnc_1";
						}
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 2)	
						{
							dialog.text = "Oh, da bist du ja, Schönheit! Dein Vater hat die gesamte Garnison aufgeboten, um dich zu finden und nach Hause zu bringen.";
							link.l1 = "Verschwinde! Ich weiß, wohin ich gehe und ich brauche deine Hilfe nicht! Kapitän, sag ihnen, sie sollen ihre Hände von mir nehmen.";
							link.l1.go = "GirlEnc_2";						
						}
						DeleteAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers");
					}
					// <-- девица в джунглях
					
					// --> Sinistra Длинные тени старых грехов
					if(CheckAttribute(pchar, "questTemp.Knippel.Soldiers_1"))
					{
						switch(0)
						{
							case 0: 
							dialog.text = "Hör zu, Charlie, wir haben einige neue Rekruten in der Festung. Grün wie Gras... Könntest du vorbeikommen und ihnen zeigen, wie man zielt?";
							link.l1 = "Wenn Kapitän Fleetwood und ich nicht in den nächsten Tagen in See stechen - gerne.";
							link.l1.go = "Knippel_Soldiers_1";
							break;
						}
						break;
					}
					
					if(CheckAttribute(pchar, "questTemp.Knippel.Soldiers_2"))
					{
						switch(0)
						{
							case 0: 
							dialog.text = "Charlie, meine Schicht ist fast vorbei, hast du Lust auf ein Getränk?";
							link.l1 = "Mit Vergnügen, Kamerad! Lassen Sie mich nur sehen, was der Kapitän will.";
							link.l1.go = "Knippel_Soldiers_2";
							break;
						}
						break;
					}
					
					if(CheckAttribute(pchar, "questTemp.Knippel.Soldiers_3"))
					{
						switch(0)
						{
							case 0: 
							dialog.text = "Gute Nacht, Charlie! Du siehst nicht so gut aus. Ist alles in Ordnung?";
							link.l1 = "Sie haben mich mitten in der Nacht geweckt, was denkst du? Kann keine Pause machen.";
							link.l1.go = "Knippel_Soldiers_3";
							break;
						}
						break;
					}
					// <-- Длинные тени старых грехов

					// --> belamour ночной приключенец
					if(CheckAttribute(pchar,"GenQuest.NightAdventureSolNum") && npchar.index == pchar.GenQuest.NightAdventureSolNum)
					{
						dialog.text = "Das Leben eines Soldaten ist geplant - Wache stehen, Patrouille ... Was willst du, "+GetAddress_Form(NPChar)+"?";
						link.l1 = "Hör mal, warst du es, mit dem hier neulich ein Betrunkener gestritten hat? Nun, anscheinend ja, mit dir...";
						link.l1.go = "NightAdventure_CitizenHomieSolder";
						break;
					}
					// <-- ночной приключенец
					
					//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
					
					// Шарль де Мор генерал-губернатор французских колоний
					if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Eure Exzellenz, Generalgouverneur! Wie kann ich dienen?";
							link.l1 = "Ich brauche nichts, danke.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Es ist mir eine große Ehre, Herr Generalgouverneur! Wie kann ich Ihnen helfen?";
								link.l1 = "Führe deinen Dienst gewissenhaft aus - ich verlange nichts mehr von dir.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Gut Sie zu sehen, Eure Exzellenz! Was kann ein bescheidener Soldat für den Gouverneur-General unserer Kolonien tun?";
								link.l1 = "Persönlich brauche ich nichts von dir. Mach weiter deinen Dienst.";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// Вице-адмирал на службе нации узнается без мундира
					if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Vizeadmiral, Eure Exzellenz! Erlaubt mir zu berichten: während meiner Wache...";
							link.l1 = "Beruhige dich, Soldat, ich brauche deinen Bericht nicht. Melde dich bei deinem Offizier.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Freut mich, Sie zu sehen, Vizeadmiral! Kann ich Ihnen bei etwas helfen?";
								link.l1 = "Nein, ich wollte nur sehen, wie aufmerksam du bist. Ich freue mich, dass du mich erkannt hast.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Vizeadmiral, das ist eine Ehre für mich! Was kann ich für Sie tun?";
								link.l1 = "Dienen "+NationNameGenitive(sti(npchar.nation))+", Soldat! Das ist das Beste, was du tun kannst.";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// Офицер с патентом
					if(IsOfficerFullEquip() && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Grüße, Kapitän! Wenn Sie Anweisungen für mich haben, dann bitte ich um Verzeihung: obwohl ich in Diensten bin "+NationNameGenitive(sti(npchar.nation))+", Ich antworte nur dem Kommandanten und dem Gouverneur."; 
							link.l1 = "Ich habe meine Offiziere und Mannschaft, die meiner Führung folgen. Erfülle deine Pflicht, Soldat.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Kapitän, können Sie mich an Bord Ihres Schiffes aufnehmen? Derselbe Dienst für "+NationNameGenitive(sti(npchar.nation))+", aber ich bevorzuge das Meer."; 
								link.l1 = "Du bist dort benötigt, wo du eingeteilt wurdest, also erfülle deinen Dienst mit Ehre. Du schließt für eine Sekunde die Augen, und sie werden es aufs Meer nehmen.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Oh, du hast Glück: du bist Kapitän des Schiffes im Dienst von "+NationNameGenitive(sti(npchar.nation))+"... Und ich bin den ganzen Tag hier festgeklebt."; 
								link.l1 = "Glaubst du, ich bin gerade erst in der Karibik angekommen und wurde eine Woche später Kapitän? Das sind alles Jahre harter Arbeit...";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// <-- legendary edition
					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = "Siehst du nicht? Ich bin im Dienst. Hör auf, mich zu belästigen.";
							link.l1 = "In Ordnung, in Ordnung...";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "Wirst du mir von verdächtigen Aktivitäten erzählen?";
							link.l1 = "Nein, überhaupt nicht, und übrigens bin ich Kapitän. Ich sehe, du hörst nicht mehr zu? Tschüss.";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "Das ist eine militärische Einrichtung, also machen Sie hier nicht zu viel Lärm.";
							link.l1 = "In Ordnung, ich werde das im Kopf behalten.";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "Solch schönes Wetter, und ich bin dazu verdammt, hier zu stehen. In der Stadt gibt es wenigstens Mädchen, und was haben wir hier? Nur Ratten herum.";
							link.l1 = ""+GetSexPhrase("Ich fühle mit dir, aber es gibt nichts, was ich tun kann, um zu helfen - es ist schließlich deine Pflicht.","He! Was ist falsch mit mir? Bin ich kein Mädchen?")+"";
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "Wenn du gerne redest, such dir jemand anderen. Ich muss hier für Ordnung sorgen und habe keine Zeit für billiges Gerede.";
							link.l1 = "Ach nein, ich schaue nur nach, ob du noch lebst. Du standest da wie eine Statue.";
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = "Du denkst wahrscheinlich, dass die Arbeit in der Garnison ein Kinderspiel ist? Absolut nicht! Es ist eine harte und wichtige Arbeit. Ich erinnere mich an einmal... ";
							link.l1 = "Du wirst mir diese Geschichte ein anderes Mal erzählen. Ich habe jetzt ein bisschen Eile.";
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = "Sei vorsichtig hier, du bist in einer Festung! Sei so leise wie eine Maus!";
							link.l1 = "Wie du sagst, Soldat.";
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = "He! Haben Sie vielleicht Wasser? Ich sterbe vor Durst.";
							link.l1 = "Nein, Freund, hab Geduld...";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = "Wie langweilig ist das Garnisonsleben, nur Tölpel wie du sind hier! Nun, die Stadtwache hat sicherlich bessere Zeiten...";
							link.l1 = "Und du nennst das 'Dienst tun'? So lässt du sicher einen Spion an dir vorbeischlüpfen!";
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = ""+GetSexPhrase("Du siehst aus wie ein starker Kerl, nicht wahr? Möchtest du dich für den Dienst in der Garnison der Festung anmelden? Wir haben geräumige Kasernen, zwei Mahlzeiten am Tag und gratis Booze.","Oh, junge Dame, Sie haben keine Ahnung, wie angenehm es ist, eine so nette Dame in diesem Nirgendwo zu treffen!")+"";
							link.l1 = ""+GetSexPhrase("Das ist sicherlich verlockend, aber ich muss trotzdem ablehnen. All diese Kaserneübungen sind einfach nichts für mich.","Danke für das Kompliment, Soldat.")+".";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "Diese verdammte Hitze... Ich würde gerne die Hälfte meines Lebens geben, um zurück nach Europa zu gehen.";
							link.l1 = "Ja, ich kann sehen, dass deine Gesundheit nicht für das lokale Klima geeignet ist.";
							link.l1.go = "exit";
						break;

					}
					// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
					/* link.l3 = "Einen Moment. Ich wollte etwas fragen "+GetSexPhrase("wollte","wollte")+"...";
					link.l3.go = "quests";//(перессылка в файл города) */				
				}
			}
		break;
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = RandPhraseSimple("Es scheint mir, das ist eine Art Schwindel. Lassen Sie uns mit dem Kommandanten sprechen, "+GetSexPhrase("Kamerad","Schatzi")+", und finde alles heraus...","Hmm... Etwas sagt mir, dass du nicht der bist, für den du dich ausgibst... Leg deine Waffe nieder "+GetAddress_Form(npchar)+", und folge mir zur weiteren Untersuchung!");
			link.l1 = RandPhraseSimple("Zum Teufel mit dir!","Wenn zwei Sonntage in einer Woche kommen...");
			link.l1.go = "fight";
			if (!CheckAttribute(pchar,"questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		
		case "NotPegYou":
			dialog.text = RandPhraseSimple("Oh, ich sehe... Alles scheint in Ordnung zu sein, du kannst gehen, "+GetAddress_Form(pchar)+".","Ich muss wohl ein wenig müde geworden sein, Wache zu stehen... Alles scheint in Ordnung zu sein, "+GetAddress_Form(pchar)+", es tut mir leid.");
			link.l1 = "Kein Problem!";
			link.l1.go = "exit";
			if (!CheckAttribute(pchar,"questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		
		case "vincento":
			dialog.text = RandPhraseSimple("Oh, ich sehe... Alles scheint in Ordnung zu sein, du kannst gehen, "+GetAddress_Form(pchar)+".","Lass uns mal sehen... Nun, alles scheint in Ordnung zu sein, "+GetAddress_Form(pchar)+", es tut mir leid.");
			link.l1 = "Das wird dir eine Lektion sein!";
			link.l1.go = "exit";
		break;
		
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				dialog.text = "Mir fällt gerade ein! Solche Unverschämtheit! Hierher zu kommen unter dem Vorwand eines Kaufmanns! Deine Bilder hängen in jeder Kaserne, du Bastard! Diesmal kommst du nicht davon! Ergreift ihn!";
				link.l1 = RandPhraseSimple("Arrgh!..","Nun, du hast danach gefragt...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (pchar.location != "LosTeques_town" && findsubstr(pchar.location.from_sea, "_town" , 0) == -1) //если причалил не в городе 300912
			{
				dialog.text = "Sie sind gekommen, um hier zu handeln? Darf ich fragen, wie? Wo ist Ihr Schiff? Sie wissen, es sieht alles sehr verdächtig aus und ich bin gezwungen, Sie festzuhalten, bis wir alles herausgefunden haben. Übergeben Sie Ihre Waffe und folgen Sie mir!";
				link.l1 = RandPhraseSimple("Fick dich!","Wenn zwei Sonntage in einer Woche kommen...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (iTemp == -1)
			{
				dialog.text = "Ihre Lizenz muss widerrufen werden, da sie abgelaufen ist und aus diesem Grund nicht gültig ist. Geben Sie Ihre Waffe ab und folgen Sie mir zur weiteren Untersuchung!";
				link.l1 = RandPhraseSimple("Leck mich!","Wenn zwei Sonntage in einer Woche kommen...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Hmm... Alles sieht in Ordnung aus. Trotzdem muss ich anmerken, dass Ihre Lizenz heute abläuft. Dieses Mal werde ich Sie durchlassen, aber Sie müssen immer noch eine neue Lizenz erwerben.";
				link.l1 = "Danke, ich werde mir bei nächster Gelegenheit eine neue besorgen.";
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = "Hmm... Alles sieht gut aus. Dennoch muss ich anmerken, dass Ihre Lizenz bald abläuft. Sie ist nur noch gültig für "+FindRussianDaysString(iTemp)+". Behalte das im Kopf, "+GetAddress_Form(npchar)+".";
				link.l1 = "Danke, ich werde mir bei nächster Gelegenheit ein neues besorgen.";
				link.l1.go = "exit";			
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase("Nun, alles sieht gut aus. Ihre Lizenz ist noch gültig für weitere "+FindRussianDaysString(iTemp)+". Du darfst passieren.","Alles ist klar, "+GetAddress_Form(npchar)+". Sie können die Stadt frei betreten und verlassen, Ihre Lizenz ist noch für einen weiteren "+FindRussianDaysString(iTemp)+". Entschuldigung für die Störung.","Alles sieht gut aus, "+GetAddress_Form(npchar)+", Ich halte dich nicht länger hier.");
				link.l1 = RandPhraseSimple("Ausgezeichnet. Herzliche Grüße.","Danke, Offizier.");
				link.l1.go = "exit";
			}
		break;
		//============================== ноды маяка Порт Рояля =========================
		case "PortRoyal_Mayak":
			dialog.text = RandPhraseSimple("Hallo, Kumpel, zerstöre nichts im Leuchtturm.","Dieser Leuchtturm ist ein sehr wichtiges Stadtbauwerk. Sei vorsichtig!");
			link.l1 = RandPhraseSimple("In Ordnung, mach dir keine Sorgen.","In Ordnung, mach dir keine Sorgen.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Mayak";
		break;
		case "PortRoyal_Gans":
			dialog.text = LinkRandPhrase("Geh nicht nahe an die Kanonen - es ist eine militärische Einrichtung!","Fremden ist es nicht erlaubt, sich den Kanonen zu nähern!","Wenn ich bemerke, dass du in der Nähe der Kanonen herumlungern, bist du erledigt!");
			link.l1 = RandPhraseSimple("Ich habe es.","In Ordnung, ich habe es verstanden.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Gans";
		break;

		// --> генератор "A damsel in the jungle"
		case "GirlEnc_1":
			dialog.text = "Und wer sind Sie, Kapitän? Sind Sie nicht zufällig ein Komplize des berüchtigsten Diebes in dieser Siedlung?";
			link.l1 = "Wen hast du gerade einen Komplizen genannt?! Bist du sonnenverwirrt oder was?! Hey, nimm deine Pranken von dem Mädchen weg!";
			link.l1.go = "GirlEnc_11";
			link.l2 = "Eigentlich habe ich "+GetSexPhrase("lernte sie kennen","lernte sie kennen")+" vor kurzem...";
			link.l2.go = "GirlEnc_12";
		break;

		case "GirlEnc_11":
			dialog.text = ""+GetSexPhrase("Herr","Fräulein")+", wir haben den Befehl, sie festzunehmen und sie in den Kerker zu bringen. Und wenn du denkst, dass du uns aufhalten kannst, irrst du dich.";
			link.l1 = "Lass uns mal sehen, dann...";
			link.l1.go = "GirlEnc_11End";
		break;

		case "GirlEnc_11End":
			DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "GirlEnc_12":
			dialog.text = "Oh, wirklich? In diesem Fall würde ich Ihnen raten, Ihre Taschen zu überprüfen. Diese Dame ist eine Profi, wissen Sie";
			link.l1 = "Danke, das werde ich tun. Wie konnte ich nur so ein Narren aus mir machen...";
			link.l1.go = "GirlEnc_12End";		
		break;		
		
		case "GirlEnc_12End":
			pchar.money = sti(pchar.money) - makeint(sti(pchar.money)/20);
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "GirlEnc_2":
			dialog.text = ""+GetSexPhrase("Herr","Fräulein")+", wir haben den Auftrag, diese Dame zu finden und sie zu ihrem Vater zu bringen.";
			link.l1 = "Nun, ein Befehl ist ein Befehl - mach weiter, dann.";
			link.l1.go = "GirlEnc_2End";
			link.l2 = "Zu spät dafür, denn ich spreche bereits mit ihrem Vater.";
			link.l2.go = "GirlEnc_21";
		break;
		
		case "GirlEnc_2End":
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("JungleGirl", "11");	
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));	
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "GirlEnc_21":
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < rand(100))
			{
				dialog.text = "Kapitän, wir haben einen Befehl, und wenn Sie denken, dass Sie uns stoppen können, irren Sie sich.";
				link.l1 = "Lass uns sehen, dann...";
				link.l1.go = "GirlEnc_21End";
			}
			else
			{
				dialog.text = "Heh, "+GetSexPhrase("du bist ein glücklicher Mann","du bist ein glückliches Mädel")+". Ihr Vater versprach eine großzügige Belohnung für denjenigen, der sie zu ihm zurückbringt.";
				link.l1 = "Verzweifle nicht - es warten noch viele Belohnungen auf dich.";
				link.l1.go = "exit";			 
			}
		break;
		
		case "GirlEnc_21End":
			DialogExit();
			AddQuestRecord("JungleGirl", "12");
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;
		// <-- генератор "A damsel in the jungle"
		// --> belamour ночной приключенец
		case "NightAdventure_CitizenHomieSolder":
			dialog.text = "Ja, bei mir. Lassen Sie ihn hinter Gittern sitzen, über sein Verhalten nachdenken. Und wenn Sie gekommen sind, um mich wegen ihm zu bedrohen, dann glauben Sie mir: Ich kann sogar den Kommandanten des Forts erreichen.";
			link.l1 = "Ja, ich kam nicht um zu drohen, sondern um Sie zu bitten, Ihre Ansprüche gegen ihn zurückzuziehen. Sie sehen, er ist ein alter Bekannter von mir, er hat sich nur betrunken, aber für einen Betrunkenen, wissen Sie, ist das Meer knietief ...";
			link.l1.go = "NightAdventure_CitizenHomieSolder_1";
		break;
		
		case "NightAdventure_CitizenHomieSolder_1":
			dialog.text = "Das heißt, er hat mir ein blaues Auge geschlagen, während ich im Dienst war, und jetzt soll er freigelassen werden? Warum sollte das passieren?";
			link.l1 = "Wie wäre es mit fünfhundert Pesos als Entschuldigung für sein Verhalten?";
			link.l1.go = "NightAdventure_CitizenHomieSolder_2";
		break;
		
		case "NightAdventure_CitizenHomieSolder_2":
			dialog.text = "Glaubst du das? Er hat meiner Ehre beleidigt, und du denkst, das kann für fünfhundert Pesos vergeben werden? Glaubst du, meine Ehre kann gekauft werden?";
			link.l1 = "..., Freund.";
			link.l1.go = "NightAdventure_CitizenHomieSolder_3";
		break;
			
		case "NightAdventure_CitizenHomieSolder_3":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderNM")
			{
				DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
				pchar.quest.NightAdventure_SeaExit.over = "yes";
				pchar.quest.NightAdventure_JungleExit.over = "yes";
				SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
				dialog.text = "Nein, Kapitän, es ist alles fair. Er hat es verdient. Und ich bitte Sie, mich nicht mehr von meinem Dienst abzulenken.";
				link.l1 = "Nun, du hast recht.";
				link.l1.go = "exit";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderGM")
			{
				dialog.text = "Tausend. Und kein Peso weniger.";
				link.l1 = "Nein, vielleicht bin ich nicht bereit, so viel für einen blauen Fleck zu bezahlen.";
				link.l1.go = "NightAdventure_CitizenHomieSolder_3NM";
				if (sti(pchar.money) >= 1000)
				{
					link.l2 = "Oh... Gut, warte mal. Hier sind sofort ein Feder und Pergament. Schreibe, dass du alle Ansprüche gegen meinen Freund zurückziehst.";
					link.l2.go = "NightAdventure_CitizenHomieSolder_3GM";
				}
			}
		break;
		
		case "NightAdventure_CitizenHomieSolder_3NM":
			DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			dialog.text = "Dann bitte ich Sie, mich nicht mehr von meinem Dienst abzulenken.";
			link.l1 = "Ich werde nicht.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_CitizenHomieSolder_3GM":
			DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
			pchar.GenQuest.NightAdventureToPrisoner = true;
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Hier bist du.";
			link.l1 = "Viel Glück bei der Arbeit.";
			link.l1.go = "exit";
		break;
		// <-- ночной приключенец
		
		// --> Sinistra Длинные тени старых грехов
		case "Knippel_Soldiers_1":
			dialog.text = "Und vielleicht lehrst du ihnen auch einige deiner Geheimnisse, damit sie nicht mit dir ins Grab gehen?";
			link.l1 = "Heh-heh, äh, nein, Kumpel, meine Geheimnisse gehören nur mir allein, und was für Geheimnisse wären das dann?";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_1");
			pchar.questTemp.Knippel.Soldiers_2 = true;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Knippel_Soldiers_2":
			dialog.text = "Hab's kapiert, du wirst wieder abhauen, wie immer.";
			link.l1 = "Nun, wenn der Fisch entkommt - ist das ein schlechter Fischer. Es ist wie mit Kanonenkugeln - eine gute versagt nie, zielt nur gut...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_2");
			pchar.questTemp.Knippel.Soldiers_3 = true;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Knippel_Soldiers_3":
			dialog.text = "Zumindest stehst du nicht jede Nacht auf. Und du verbringst mehr Zeit auf dem Schiff als an Land. Mit wem redest du?";
			link.l1 = "Ach, was weißt du schon über die Härten des Dienstes, Kumpel! Wie es in der königlichen Marine war!.. Du kannst es dir nicht einmal vorstellen.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_3");
			LAi_CharacterDisableDialog(npchar);
		break;
		// <-- Длинные тени старых грехов
		
		//замечение по обнажённому оружию
		case "SoldierNotBlade":
			// belamour legendary edition если у герой офицер нации -->
			if(IsOfficerFullEquip())
			{
			dialog.text = "Kapitän, ich bitte Sie, Ihre Waffen wegzulegen: es ist verboten, sie in unserer Stadt zu ziehen.";
			link.l1 = LinkRandPhrase("In Ordnung, ich räume es weg...","Bereits erledigt.","Wie du sagst...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Leck mich!","Ich denke, ich werde es benutzen!","Ich werde es zur rechten Zeit weglegen.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
			}
			// <-- legendary edition
			dialog.text = LinkRandPhrase("He, was soll das ganze Waffenschwingen?! Leg es sofort weg!","Ich befehle Ihnen, Ihre Waffe sofort wegzulegen!","Hallo, "+GetAddress_Form(NPChar)+", hör auf, die Leute zu erschrecken! Leg deine Waffe weg.");
			link.l1 = LinkRandPhrase("In Ordnung, ich räume es weg...","Bereits erledigt.","Wie du sagst...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Leck mich!","Ich denke, ich werde es benutzen!","Ich werde es weglegen, wenn die Zeit reif ist.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;

		case "pirate_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			DoQuestFunctionDelay("TownPirate_battle", 0.5);
		break;
	}
}
