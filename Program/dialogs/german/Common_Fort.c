// boal 25/04/04 общий диалог солдат форта
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
    /* // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Fort\" + NPChar.City + "_Fort.c";
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
				dialog.text = RandPhraseSimple("Ein Spion! Gib deine Waffe ab und folge mir!","Ein feindlicher Agent! Ergreife "+GetSexPhrase("ihn","sie")+"!");
				link.l1 = RandPhraseSimple("Halt den Mund, Weichei!","Verpiss dich!");
				link.l1.go = "fight"; 
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (GetRelation2BaseNation(sti(npchar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					dialog.text = RandPhraseSimple("Wer bist du und was machst du hier?","Halt still! Wer bist du? Aus welchem Grund versuchst du, das Fort zu betreten?");
					//==> по лицензии
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Offizier, ich habe "+GetRusNameNationLicence(sti(npchar.nation))+", also bin ich hier auf legalen Grundlagen. Hier, bitte schau mal...";
						link.l1.go = "LicenceOk";
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (sti(pchar.nation) == PIRATE)
						{
    						dialog.text = RandPhraseSimple("Pirat ist in der Festung?! Ergreifen"+GetSexPhrase("ihn","sie")+"!","Das ist ein Pirat, der in unserer Festung herumschnüffelt! Ab ins Gefängnis!!!");
							link.l1 = RandPhraseSimple("Ja, ich bin ein Pirat, und jetzt?","Heh, fang mich wenn du kannst...");
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = "Siehst du nicht die Flagge von "+NationNameGenitive(sti(pchar.nation))+" auf dem Mast meines Schiffes?!";
						}
						else //если причалил не в городе
						{
							link.l1 = "Ich habe den Anker in der Nähe fallen lassen "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" unter der Flagge von"+NationNameGenitive(sti(pchar.nation))+"! Brauchen Sie noch etwas?";
						}
						// belamour legendary edition вызываюий доверие даёт возможность обмануть стражу
						if(sti(pchar.reputation.fame) < 41 && CheckCharacterPerk(pchar, "Trustworthy"))
						{
							Notification_Perk(true, "Trustworthy");
							link.l1.go = "NotPegYou";
						}
						else
						{
							if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50)))
							{
								notification("Skill Check Failed", SKILL_SNEAK);
								link.l1.go = "PegYou";
							}
							else
							{
								link.l1.go = "NotPegYou";
							}
						}
					}
				}
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn)) // наш горожанин
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = "Oh, Kapitän, wir hatten eine so tolle Zeit mit dir auf See! So viele Schiffe haben wir zusammen unter deinem Kommando versenkt! Und hier...";
									link.l1 = "Und hier, mein Freund, kannst du deinen Augen einen Schmaus mit reizenden Damen gönnen, die du auf See nicht sehen wirst.";
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = "Kapitän, was haben wir getan, um das zu verdienen?! Wir sind doch keine Landratten, oder?";
									link.l1 = "Ruhe, Seemann! Dein Posten ist ein sehr wichtiger und ehrenhafter, also hör auf zu jammern.";
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = "Was passiert auf See, Kapitän? Werden wir es jemals wieder sehen?";
									link.l1 = "Aber natürlich, Seemann! Sobald du von deiner Pflicht entbunden bist, kannst du zum Pier gehen und das Meer so sehr genießen, wie du möchtest.";
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = "Ich möchte mich beschweren, Kapitän: Uns fehlt allen das Meer. Wir sind alle total genervt von diesem Landdienst!";
									link.l1 = "Ich werde müde von diesem Gejammer! Du hast hier auch genug Rum! Bediene dort, wo dich der Kapitän hingestellt hat, oder jemand wird als Beispiel für andere gehängt.";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "Ich sage Ihnen im Vertrauen, Kapitän, der neue Gouverneur ist ein Bestecher und Veruntreuer. Aber das ist wirklich nicht mein Bier...";
									link.l1 = "Genau, Freibeuter. Deine Aufgabe ist es, an deinem Posten zu stehen und für Ordnung zu sorgen. Und den Gouverneur am Rah zu hängen, das ist meine Aufgabe. Gute Arbeit!";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "Danke, dass Sie uns nicht vergessen haben, Kapitän! Wir würden Ihnen durch Feuer und Wasser folgen!";
									link.l1 = "Ich kenne deinen Typ, Gauner! Alles, was ihr wirklich liebt, ist Gold. Heute Abend gibt es eine Party in der Taverne, Getränke gehen auf mich. Vergiss nicht zu kommen.";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "Heh, Kapitän! Denk mal nach, kann ein Korsar wirklich ein Hüter der Ordnung sein?! Es ist so lange her, seit wir das letzte Mal im echten Geschäft waren!";
									link.l1 = "Keine Zeit zum Ausruhen, Korsar! Feindliche Flotten durchkämmen die Gewässer in der Nähe unserer Inseln, und wir müssen jederzeit für ein Blutbad bereit sein.";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "Kapitän, ich habe gehört, dass die Krone ein weiteres Geschwader auf uns angesetzt hat?";
									link.l1 = "Natürlich, Freibeuter. Solange wir leben, wird es keinen Frieden für uns geben. Und sogar in der Hölle werden wir gegen Teufel kämpfen!";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "Yo-ho-ho! Verdammt, das war ein wirklich starker Schnaps gestern, Kapitän! Schade, dass Sie nicht dabei waren.";
									link.l1 = "Keine große Sache, ich werde es wieder gut machen. Und ich beneide euch nicht, Jungs.";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "Ich verrate es Ihnen im Vertrauen, Kapitän, weil Sie uns immer gut behandelt haben, wir hatten gestern eine gute Zeit mit einer wirklich netten Braut...";
									link.l1 = "Heh, Freibeuter, ein Strick ist etwas, das du wirklich brauchst!";
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = "Kapitän! Bitte, entbinden Sie mich von dieser verfluchten Pflicht! Ich kann einfach nicht mehr die Rolle eines Hüters der Ordnung spielen.";
									link.l1 = "Nachtwache auf einem Schiff ist auch nicht leicht. Freund, Pflicht ist Pflicht, egal was und wo es ist.";
									link.l1.go = "exit";
								break;
							}
							// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
							/* link.l2 = RandPhraseSimple("Es gibt eine wichtige Angelegenheit!","Ich habe ein Anliegen an dich.");
							link.l2.go = "quests";//(перессылка в файл города) */
							break;
						}
					}
					
					//Jason --> мини-квест Дефицитный товар
					if (!CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && sti(pchar.rank) < 4 && !CheckAttribute(pchar, "questTemp.Wine") && npchar.location.group == "soldiers")
					{// Addon 2016-1 Jason пиратская линейка
						string wineCity = "FortFrance";
						if(SandboxMode)
						{
							if(CheckAttribute(pchar,"HeroParam.ToCityId"))
							{
								wineCity = pchar.HeroParam.ToCityId;	
							}
						}
						if(GetCityNameByIsland(LoadedLocation.islandId) ==  wineCity && npchar.location.locator == "protector1")
						{
							dialog.text = "He, Kumpel! Kannst du mir einen kleinen Gefallen tun?";
							link.l1 = "Hängt davon ab, was getan werden muss.";
							link.l1.go = "Wine_soldier";
							link.l2 = "Ich habe keine Zeit für so etwas.";
							link.l2.go = "exit";
							pchar.questTemp.Wine = "true";
							DelLandQuestMark(npchar);
							break;
						}
						if(StartHeroType == 2)
						{
							if(LoadedLocation.id == "Santiago_fort")
							{
								dialog.text = "Hallo, Kumpel! Kannst du mir einen kleinen Gefallen tun?";
								link.l1 = "Es hängt davon ab, was getan werden muss.";
								link.l1.go = "Wine_soldier";
								link.l2 = "Ich habe keine Zeit für sowas.";
								link.l2.go = "exit";
								pchar.questTemp.Wine = "true";
								DelLandQuestMark(npchar);
								break;
							}
						}
					}
					// <-- мини-квест Дефицитный товар
					
					//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
					
					// Шарль де Мор генерал-губернатор французских колоний
					if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Eure Exzellenz, Gouverneur General! Was darf ich servieren?";
							link.l1 = "Ich brauche nichts, danke.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Es ist eine große Ehre für mich, Herr Gouverneur General! Wie kann ich Ihnen helfen?";
								link.l1 = "Führe deinen Dienst gewissenhaft aus - Ich verlange nichts weiter von dir.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Gut Sie zu sehen, Eure Exzellenz! Was kann ein bescheidener Soldat für den Generalgouverneur unserer Kolonien tun?";
								link.l1 = "Persönlich brauche ich nichts von dir. Mach weiter so.";
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
							dialog.text = "Vizeadmiral, Eure Exzellenz! Erlauben Sie mir zu berichten: während meiner Wache...";
							link.l1 = "Beruhige dich, Soldat, ich brauche deinen Bericht nicht. Melde dich bei deinem Chef.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Freut mich, Sie zu sehen, Vizeadmiral! Kann ich Ihnen bei etwas helfen?";
								link.l1 = "Nein, ich habe nur überprüft, wie aufmerksam du bist. Ich bin froh, dass du mich erkannt hast.";
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
							dialog.text = "Grüße, Kapitän! Wenn Sie irgendwelche Anweisungen für mich haben, dann bitte ich um Verzeihung: obwohl ich in Diensten bin "+NationNameGenitive(sti(npchar.nation))+", ich antworte nur dem Kommandanten und dem Gouverneur."; 
							link.l1 = "Ich habe meine Offiziere und Mannschaft, die meiner Führung folgen. Tu deine Pflicht, Soldat.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Kapitän, könnten Sie mich in Ihren Dienst auf Ihrem Schiff nehmen? Der gleiche Dienst für "+NationNameGenitive(sti(npchar.nation))+", aber ich bevorzuge das Meer."; 
								link.l1 = "Du bist dort benötigt, wo du eingeteilt wurdest, also erfülle deinen Dienst mit Ehre. Du schließt deine Augen für eine Sekunde, und sie werden es aufs Meer nehmen.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Oh, du hast Glück: du bist Kapitän eines Schiffes im Dienst von "+NationNameGenitive(sti(npchar.nation))+"... Und ich stecke hier den ganzen Tag fest."; 
								link.l1 = "Glaubst du, ich bin gerade in der Karibik angekommen und eine Woche später Kapitän geworden? Das sind alles Jahre harter Arbeit...";
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
							link.l1 = "Schon gut, schon gut...";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "Werden Sie mir von verdächtigen Aktivitäten erzählen?";
							link.l1 = "Nein, überhaupt nicht, übrigens bin ich Kapitän. Ich sehe, du hörst nicht mehr zu? Tschüss.";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "Dies ist eine militärische Einrichtung, also machen Sie hier nicht zu viel Lärm.";
							link.l1 = "In Ordnung, ich werde das im Hinterkopf behalten.";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "So ein schönes Wetter, und ich muss hier stehen. In der Stadt gibt es wenigstens Mädchen, und was haben wir hier? Nur Ratten herum.";
							link.l1 = ""+GetSexPhrase("Ich sympathisiere, aber es gibt nichts, was ich tun kann, um zu helfen - es ist schließlich deine Pflicht.","He! Was ist los mit mir? Bin ich kein Mädchen?")+"";
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "Wenn du gerne redest, such dir jemand anderen. Ich muss hier für Ordnung sorgen und habe keine Zeit für billiges Geschwätz.";
							link.l1 = "Oh, nein, ich überprüfe nur, ob du noch lebst. Du standest da wie eine Statue.";
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = "Du denkst wahrscheinlich, dass die Arbeit in der Garnison ein Kinderspiel ist? Absolut nicht! Es ist eine harte und wichtige Arbeit. Ich erinnere mich einmal... ";
							link.l1 = "Du wirst mir die Geschichte ein andermal erzählen. Ich habe jetzt ein bisschen Eile.";
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = "Vorsicht hier, du bist in einer Festung! Sei so leise wie eine Maus!";
							link.l1 = "Wie du sagst, Soldat.";
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = "He! Haben Sie zufällig Wasser? Ich sterbe vor Durst.";
							link.l1 = "Nein, Kumpel, behalte deine Geduld...";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = "Wie langweilig ist das Garnisonsleben, nur Bauern wie du in der Nähe! Nun, die Stadtwache hat sicherlich bessere Zeiten...";
							link.l1 = "Und das nennst du 'Dienst tun'? So lässt du sicher einen Spion an dir vorbeischlüpfen!";
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = ""+GetSexPhrase("Sie sehen aus wie ein starker Kerl, nicht wahr? Möchten Sie sich für den Dienst in der Garnison des Forts anmelden? Wir haben geräumige Kasernen, zwei Mahlzeiten am Tag und kostenlosen Schnaps.","Oh, junge Dame, Sie haben keine Ahnung, wie angenehm es ist, in dieser gottverlassenen Gegend so eine nette Maid zu treffen!")+"";
							link.l1 = ""+GetSexPhrase("Das ist sicherlich verlockend, aber ich muss trotzdem ablehnen. All diese Kasernendrills sind einfach nichts für mich.","Danke für das Kompliment, Soldat.")+".";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "Diese verfluchte Hitze... Ich würde ohne zu zögern die Hälfte meines Lebens opfern, um zurück nach Europa zu gehen.";
							link.l1 = "Ja, ich sehe, dass deine Gesundheit nicht für das hiesige Klima geeignet ist.";
							link.l1.go = "exit";
						break;
					}
					// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
					/* link.l3 = "Na ja... klar. Ich wollte nur das "+GetSexPhrase("wollte","wollte")+" fragen...";
					link.l3.go = "quests";//(перессылка в файл города) */
				}
			}
		break;
		
		//Jason --> мини-квест Дефицитный товар
		case "Wine_soldier":
			dialog.text = "Sie sehen, ich möchte unbedingt etwas Wein... Aber nicht den lokalen Fusel aus faulen Früchten, der für zwei Pesos pro Fass verkauft wird - ich möchte eine Flasche echten europäischen Weins. Sie können ihn in der Stadt von den Händlern bekommen. Er ist ziemlich teuer, aber ich werde voll bezahlen und sogar dreihundert Pesos oben drauf legen. Also, bringen Sie mir etwas?";
			link.l1 = "Und warum kannst du es nicht selbst holen? Du musst nicht zu viel bezahlen, warte einfach, bis du von deinem Posten entbunden bist und mach dich auf den Weg. Wo ist der Haken?";
			link.l1.go = "Wine_soldier_1";
		break;
		
		case "Wine_soldier_1":
			dialog.text = "Es gibt keinen Haken. Ich kann das Fort einfach nicht verlassen, um in die Stadt zu gehen, bis ich meinen Urlaub bekomme, der so schnell nicht passieren wird. Außerdem hat unser Kommandant strengstens verboten, im Fort zu trinken, verdammt sei er! Also, wirst du einem Soldaten helfen?";
			link.l1 = "Nun, warum nicht? Ich bringe dir diesen Wein, ich habe sowieso etwas Freizeit.";
			link.l1.go = "Wine_soldier_2";
			link.l2 = "Es tut mir leid, Kumpel, aber das kann ich nicht tun. Such dir jemand anderen, der dir hilft.";
			link.l2.go = "exit";
		break;
		
		case "Wine_soldier_2":
			dialog.text = "Großartig! Vielen Dank! Heute habe ich Wache, also komm morgen. Du findest mich oben auf dem Fort, dort kannst du mir die Flasche zustecken, damit niemand Notiz davon nimmt...";
			link.l1 = "In Ordnung. Warte auf mich, ich werde dich morgen besuchen.";
			link.l1.go = "exit";
			pchar.questTemp.Wine.id = npchar.ID;
			pchar.questTemp.Wine.SName = GetFullName(npchar);
			pchar.questTemp.Wine.bottle = "true";
			npchar.lifeday = 5;
			SetFunctionTimerCondition("Wine_Exchange", 0, 0, 1, false);
			pchar.questTemp.Wine.City = GetCityNameByIsland(LoadedLocation.islandId);
			if(StartHeroType == 2) pchar.questTemp.Wine.City = "Santiago";
			Log_TestInfo(pchar.questTemp.Wine.City);
			SaveCurrentQuestDateParam("questTemp.Wine_bottle");
			AddQuestRecord("Wine", "0");
			SetFunctionLocationCondition("WineTraderQM", pchar.questTemp.Wine.City+"_town", 0);
		break;
		// <-- мини-квест Дефицитный товар
		
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = RandPhraseSimple("Es scheint mir, es ist eine Art Trick. Sprechen wir mit dem Kommandanten, "+GetSexPhrase("Kumpel","Schatz")+", und finde alles heraus...","Hmm... Etwas sagt mir, dass du nicht der bist, für den du dich ausgibst... Gib deine Waffe ab "+GetAddress_Form(npchar)+", und folge mir zur weiteren Untersuchung!");
			link.l1 = RandPhraseSimple("Zum Teufel mit dir!","Wenn zwei Sonntage in einer Woche kommen...");
			link.l1.go = "fight";
			if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "NotPegYou":
			dialog.text = RandPhraseSimple("Oh, ich sehe... Alles scheint in Ordnung zu sein, du kannst gehen, "+GetAddress_Form(pchar)+".","Ich muss wohl beim Wachdienst ein bisschen müde geworden sein... Alles scheint in Ordnung zu sein, "+GetAddress_Form(pchar)+", es tut mir leid.");
			link.l1 = "Kein Problem!";
			link.l1.go = "exit";
			if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				dialog.text = "Stell dir nur vor! So eine Frechheit! Hierher zu kommen unter dem Deckmantel eines Händlers! Deine Bilder hängen in jeder Kaserne, du Bastard! Dieses Mal kommst du nicht davon! Ergreift ihn!";
				link.l1 = RandPhraseSimple("Arrgh!..","Nun, du hast danach gefragt...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (findsubstr(pchar.location.from_sea, "_town" , 0) == -1) //если причалил не в городе
			{
				dialog.text = "Sie sind gekommen, um hier Handel zu treiben? Darf ich fragen wie? Wo ist Ihr Schiff? Sie wissen, das sieht alles sehr verdächtig aus, und ich bin gezwungen, Sie festzuhalten, bis wir alles herausfinden. Übergeben Sie Ihre Waffe und folgen Sie mir!";
				link.l1 = RandPhraseSimple("Leck mich!","Wenn zwei Sonntage in einer Woche kommen...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (iTemp == -1)
			{
				dialog.text = "Ihre Lizenz muss widerrufen werden, da sie abgelaufen ist und aus diesem Grund nicht gültig ist. Übergeben Sie Ihre Waffe und folgen Sie mir zur weiteren Untersuchung!";
				link.l1 = RandPhraseSimple("Leck mich!","Wenn zwei Sonntage in einer Woche kommen...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Hmm... Alles sieht in Ordnung aus. Dennoch muss ich bemerken, dass Ihre Lizenz heute abläuft. Ich werde Sie dieses Mal passieren lassen, aber Sie müssen dennoch eine neue Lizenz erwerben.";
				link.l1 = "Danke, ich werde es bei meiner frühesten Bequemlichkeit erledigen.";
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = "Hmm... Alles sieht gut aus. Trotzdem muss ich darauf hinweisen, dass Ihre Lizenz bald abläuft. Sie ist nur noch gültig für "+FindRussianDaysString(iTemp)+". Also behalte das im Hinterkopf, "+GetAddress_Form(npchar)+".";
				link.l1 = "Danke, ich werde mir bei nächster Gelegenheit eine neue besorgen.";
				link.l1.go = "exit";			
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase("Nun, alles sieht gut aus. Ihre Lizenz ist gültig für "+FindRussianDaysString(iTemp)+". Du darfst passieren.","Alles ist klar, "+GetAddress_Form(npchar)+". Sie können frei in die Stadt ein- und ausfahren, Ihre Lizenz ist gültig für  "+FindRussianDaysString(iTemp)+". Entschuldigung für die Störung.","Alles sieht gut aus, "+GetAddress_Form(npchar)+", Ich halte dich hier nicht länger fest.");
				link.l1 = RandPhraseSimple("Ausgezeichnet. Mit besten Grüßen.","Danke, Offizier.");
				link.l1.go = "exit";
			}
		break;

		//замечение по обнажённому оружию
		case "SoldierNotBlade":
			// belamour legendary edition если у герой офицер нации -->
			if(IsOfficerFullEquip())
			{
				dialog.text = "Kapitän, ich bitte Sie, Ihre Waffen wegzulegen: es ist verboten, sie in unserer Stadt zu ziehen.";
				link.l1 = LinkRandPhrase("In Ordnung, ich werde es weglegen...","Bereits erledigt.","Wie du willst...");
				link.l1.go = "exit";
				link.l2 = LinkRandPhrase("Leck mich!","Ich denke, ich werde es benutzen!","Ich werde es weglegen, wenn die Zeit reif ist.");
				link.l2.go = "fight";
				npchar.greeting = "soldier_common";
				NextDiag.TempNode = "First Time";
				break;
			}
			// <-- legendary edition
			dialog.text = LinkRandPhrase("Warum zum Teufel rennst du mit einer gezogenen Klinge herum? Steck deine Waffe sofort weg!","Ich befehle Ihnen, Ihre Waffe sofort zu verstecken!","He, "+GetSexPhrase("Kamerad","lass")+", hör auf, die Leute zu erschrecken! Stecke deine Waffe weg.");
			link.l1 = LinkRandPhrase("Gut.","Gut.","Wie du willst...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Verpiss dich!","Es schadet nicht zu träumen...","Wenn zwei Sonntage in einer Woche kommen.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
	}
}
