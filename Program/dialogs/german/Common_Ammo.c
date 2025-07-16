// диалог коменданта форта
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld, location;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
   /*NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}*/
    // вызов диалога по городам <--

	switch(Dialog.CurrentNode)
	{
		case "Exit":
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

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		
		case "First time":
			location = &Locations[FindLocation(pchar.location)];
			if (rand(4) == 4 && GetNpcQuestPastDayParam(location, "gun_date") > 365 && !CheckAttribute(pchar, "questTemp.PrisonGun"))
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Hör zu, ich habe ein wichtiges Geschäft mit dir. Ich hoffe wirklich, du könntest helfen.","Kapitän, darf ich Sie mit einem recht lukrativen Angebot interessieren?"),RandPhraseSimple("Ich denke, dass Sie uns in einer wichtigen Angelegenheit helfen könnten.","Kapitän, ich habe ein heikles Angebot für Sie, das für uns beide recht lukrativ sein könnte."));					
				link.l1 = "Nun, sprich Deinen Verstand aus, und wir werden sehen...";
				link.l1.go = "GiveTaskGun";
				location.quest.PrisonGun = "Target"; 
				SaveCurrentNpcQuestDateParam(location, "gun_date");
				break;
			}
		
			dialog.text = RandPhraseSimple("Ich bin der Kommandant der Festung. Was brauchst du hier?","Was brauchst du? Warum bist du hierher gekommen?");
			link.l1 = "Oh, nichts Besonderes, ich sehe mir nur die Stadt und ihre Umgebung an. Ich bin nur durch einen glücklichen Zufall hier gelandet.";
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// Офицер с патентом
			if(IsOfficerFullEquip())
			{
				dialog.text = "Willkommen im Fort, Kapitän. Brauchst du etwas?";
				link.l1 = "Nein, nichts, bin einfach zufällig vorbeigekommen.";
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Grüße Vizeadmiral! Haben Sie irgendwelche Befehle?";
				link.l1 = "Nein, Offizier, keine Befehle. Ich bin nur gekommen, um das Fort zu sehen.";
			}
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Gouverneur General, Eure Gnaden! Ich habe vollständige Ordnung in der Festung. Wird es irgendwelche Befehle geben?";
				link.l1 = "Ich bin froh, dass es Ihnen gut geht, Offizier. Keine Befehle, ich bin nur vorbeigekommen, um das Fort zu überprüfen.";
			}
			// <-- legendary edition
			link.l1.go = "exit";
			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_ammo" && GetQuestPastDayParam("questTemp.Wine_bottle") < 5)
			{
				link.l11 = "Ich habe eine interessante Information für Sie, Offizier. Einer Ihrer Soldaten, "+pchar.questTemp.Wine.SName+"bat mich, in der Stadt durch meine Vermittlung Wein zu kaufen. Angesichts Ihrer Befehle...";
				link.l11.go = "Wine_prison";
			}
			// <-- мини-квест Дефицитный товар
			// Карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "fraht" && NPChar.location == "portpax_ammo")
			{
				link.l11 = "Hallo, Offizier. Ich komme aus der Kolonie Basse-Terre, auf Befehl eines Mannes namens Gerard LeCroix. In meinem Laderaum gibt es eine Ladung Schießpulver und Bomben für Sie...";
				link.l11.go = "trial";
			}
			// Опасный груз -->
			if (pchar.location == "Cumana_Ammo")
			{
				if (pchar.questTemp.zpq != "begin" && pchar.questTemp.zpq != "failed" && pchar.questTemp.zpq != "completed")
				{
					link.l2 = "Sie sehen besorgt aus, Offizier. Wie kann ich Ihnen helfen?";
					link.l2.go = "zpq_prs1";
				}
				if (pchar.questTemp.zpq == "begin" && GetSquadronGoods(pchar, GOOD_POWDER) >= 15000 && GetQuestPastDayParam("pchar.questTemp.zpq") >= 7)
				{
					link.l3 = "Ich bin bereit zu melden, dass die ganze Ladung Schießpulver geliefert ist. Mein Schiff ist bereit zum Entladen.";
					link.l3.go = "zpq_ex";
				}
				if (pchar.questTemp.zpq == "begin")
				{
					link.l4 = "Ich möchte unseren Schießpulver-Deal ablehnen. Das ist zu mühsam.";
					link.l4.go = "zpq_fld2";
				}
			}
			// <-- Опасный груз
			NextDiag.TempNode = "First time";
		break;

		// --> Орудия для форта
		case "GiveTaskGun":
			dialog.Text = LinkRandPhrase("Verstehen Sie, die Fort-Kanonen sind ziemlich abgenutzt. Die Schatzkammer hat Mittel für ihren Austausch bereitgestellt, aber ich habe einfach keine Ahnung, wo ich die neuen kaufen kann: Es gibt einfach keine Möglichkeit, sie in unserer Kolonie in der benötigten Menge zu finden. Also dachte ich, dass die Kanonen von den Schiffen, die Sie geentert haben, für uns hier ziemlich nützlich sein könnten.","Ich muss die Geschützbatterie der Festung ersetzen. Die Gelder wurden bereits bereitgestellt, aber, Sie wissen... Es ist einfach unmöglich, die notwendige Menge in unserer Kolonie zu kaufen.","Ich wurde beauftragt, die verschlissenen Kanonen des Forts zu ersetzen, aber ich scheine nirgendwo genug zu finden.");
			Link.l1 = "Hmm... Könnten Sie ein wenig mehr ins Detail gehen? Kaliber, Menge, Preis?";
			Link.l1.go = "GiveTaskGun_1";
			pchar.questTemp.PrisonGun = true;
			SaveCurrentQuestDateParam("pchar.questTemp.PrisonGun");
		break;
			
		case "GiveTaskGun_1":
			GetGunType();
			pchar.questTemp.PrisonGun.Sum = makeint(sti(pchar.questTemp.PrisonGun.Price)*sti(pchar.questTemp.PrisonGun.Qty));
			pchar.questTemp.PrisonGun.Luck = rand(4);
			pchar.questTemp.PrisonGun.Id = npchar.location;
			dialog.Text = "Ich brauche "+pchar.questTemp.PrisonGun.Text+", in der Höhe von "+sti(pchar.questTemp.PrisonGun.Qty)+"  genau Einheiten. Ich werde in goldenen Dublonen bezahlen, "+sti(pchar.questTemp.PrisonGun.Price)+" für ein Stück. Das wird sich belaufen auf "+FindRussianDublonString(sti(pchar.questTemp.PrisonGun.Sum))+" insgesamt. Was wirst du sagen? Ach, und noch etwas - Ich werde die gesamte Lieferung akzeptieren, aber nicht früher als in einem Monat - das Geld ist noch nicht eingetroffen.";
			Link.l1 = RandPhraseSimple("Nein, Offizier, Ihr Angebot hat mich überhaupt nicht interessiert... Es tut mir leid.","Es ist verlockend, aber ich glaube, ich bin raus. Erlaube mir, meine Gründe für mich zu behalten.");
			Link.l1.go = "exit_gun";
			Link.l2 = RandPhraseSimple("Nun, das Angebot ist sicherlich interessant. Betrachten Sie es als abgemacht.","Ich denke, ich nehme es. Es ist nicht so schwer und offensichtlich profitabel.");
			Link.l2.go = "GiveTaskGun_2";
		break;
			
		case "exit_gun":
			dialog.Text = "So eine Schande, Kapitän, ich habe auf dich gezählt. Und... Ich hoffe doch, dass dieses Gespräch innerhalb der Festung bleibt?";
			Link.l1 = "Du musst mich nicht daran erinnern. Beste Grüße.";
			Link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
			
		case "GiveTaskGun_2":
			dialog.Text = "Nun, dann ist das ein Abkommen! Ich schränke Sie nicht auf bestimmte Bedingungen ein, aber bitte versuchen Sie, es nicht über ein halbes Jahr hinauszuzögern. Und ich hoffe, Sie verstehen, dass dies streng vertraulich ist?";
			Link.l1 = "Natürlich tue ich das. Auf Wiedersehen, Kommandant.";
			Link.l1.go = "exit";
			ReOpenQuestHeader("PrisonGun");
			AddQuestRecord("PrisonGun", "1");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			AddQuestUserData("PrisonGun", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("PrisonGun", "sQty", makeint(pchar.questTemp.PrisonGun.Qty));
			AddQuestUserData("PrisonGun", "sSum", makeint(pchar.questTemp.PrisonGun.Sum));
			AddQuestUserData("PrisonGun", "sText", pchar.questTemp.PrisonGun.Text);
			NextDiag.TempNode = "First time";
		break;	
		
		case "CheckGun":
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") < 30)
			{
				dialog.Text = "Ich habe euch gesagt, nicht früher als in einem Monat zu kommen!";
				Link.l1 = "Verdammt! Ich war so beschäftigt"+GetSexPhrase("","")+", dass ich einen verloren habe"+GetSexPhrase("","")+" die Zeit verloren... Entschuldigung, ich komme später, wie vereinbart.";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				break;
			}
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") > 180)
			{
				dialog.Text = "Hmm... Weißt du, es ist schon über ein halbes Jahr her, seit dem Tag, an dem wir unseren 'Vertrag' geschlossen haben. Ich habe die Kanonen bereits gekauft. Dachtest du wirklich, ich würde ewig auf dich warten?";
				Link.l1 = "Verdammt! Und was soll ich jetzt mit ihnen anfangen?";
				Link.l1.go = "TakeGun_late";
				break;
			}
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = GetSquadronGoods(Pchar, iGunGoods) - sti(pchar.questTemp.PrisonGun.Qty);
			sTemp = sti(pchar.questTemp.PrisonGun.Qty);
			iTest = FindColony(NPChar.City); // город
			
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.Text = "Ja, bist du bereit, mir zu helfen?";
				if (amount < 0)
				{
					Link.l1 = "Nein, immer noch in Arbeit. Wollte nur sicherstellen, dass unser Geschäft noch steht.";
					Link.l1.go = "exit";
				}
				else
				{
					Link.l1 = "Ich bin's. Die gesamte Ladung befindet sich im Laderaum - "+sTemp+" Einheiten, wie vereinbart.";
					Link.l1.go = "TakeGun";
				}
			}
			else 
			{
				dialog.text = "Ich sehe Ihr Schiff nicht im Hafen. Schlagen Sie vor, diese Kanonen durch den Dschungel zu schleppen? Macht schnell zu unserem Hafen und kommt zurück.";
				link.l1 = "Mein Schiff ist auf der anderen Seite der Insel. Ich werde es zum Hafen bringen.";
				link.l1.go = "exit";
			}
		break;
		
		case "TakeGun":
			if (pchar.questTemp.PrisonGun.Luck == 4)
			{
				dialog.Text = RandPhraseSimple("Weißt du, es ist wirklich unangenehm, aber ich muss unseren Deal anprangern. Wir hatten gerade eine Finanzinspektion, und du weißt, wie gewissenhaft sie in solchen Dingen sind. Ich kann einfach nichts tun. Es tut mir Leid.","Kapitän, Sie wissen... Nun, Kanonen wurden uns aus der Metropole geschickt, und ich war natürlich gezwungen, sie auszulösen. Wucherpreise, aber... Es tut mir wirklich leid, dass ich Sie enttäuscht habe... Mir geht es auch nicht gut dabei.");
				Link.l1 = "Verdammt! Und was soll ich jetzt mit ihnen anfangen?";
				Link.l1.go = "TakeGun_no";
			}
			else
			{
				dialog.Text = RandPhraseSimple("Ausgezeichnet. Ich werde eine Truppe aus der Garnison senden, um sie zu entladen.","Ausgezeichnet. Meine Soldaten werden Ihnen helfen, die Kanonen zu entladen.");
				Link.l1 = "Haben Sie die Zahlung vorbereitet?";
				Link.l1.go = "TakeGun_1";
			}
		break;
		
		case "TakeGun_no":
			dialog.Text = "Ich weiß es nicht. Verkaufe sie im Schiffswerft, rüste ein Handelsschiff aus, versenke sie... Ich habe wirklich keine Ahnung. Und bitte, erzähl niemandem von diesem Geschäft.";
			Link.l1 = "Oh, du sagst es! Ich habe einfach keine Worte!";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "3");
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		
		case "TakeGun_late":
			dialog.Text = "Ich habe keine Ahnung. Es ist dein Problem. Verkaufe sie, wirf sie weg, versenke sie - es ist mir wirklich egal.";
			Link.l1 = "Oh, das war einfach Zeitverschwendung...";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "4");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		
		case "TakeGun_1":
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = sti(pchar.questTemp.PrisonGun.Qty);
			iTemp = sti(pchar.questTemp.PrisonGun.Sum);
			dialog.Text = "Natürlich. Hier ist dein Gold - bedien dich.";
			Link.l1 = "Danke! Es war ein Vergnügen, Geschäfte mit dir zu machen!";
            Link.l1.go = "TakeGun_2";
			TakeNItems(pchar, "gold_dublon", iTemp);
			Log_Info("You have received "+FindRussianDublonString(sti(pchar.questTemp.WPU.Escort.Money))+"");
			PlaySound("interface\important_item.wav");
			RemoveCharacterGoods(Pchar, iGunGoods, amount);
		break;
		
		case "TakeGun_2":
			dialog.Text = "Das Gefühl ist gegenseitig. Du warst sehr hilfreich. Und, ich bitte dich, behalte diesen Deal in diesem Raum.";
			Link.l1 = "Natürlich. Die besten Wünsche für dich.";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "2");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		// <-- орудия для форта

		//Jason --> мини-квест Дефицитный товар
		case "Wine_prison":
			dialog.text = "Was?! Ich habe strengstens untersagt, auf dem Territorium des Forts zu trinken! Nun, er wird dafür bezahlen müssen. Ich werde ihm 1000 Pesos von seiner Bezahlung abziehen und sie dir als Belohnung für deine Wachsamkeit übergeben. Und dieser Kerl wird für drei Tage in Haft sitzen.";
			link.l1 = "Danke, "+GetAddress_FormToNPC(NPChar)+". Solche Verstöße zu stoppen ist unsere gemeinsame Pflicht.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 1000);
			ChangeCharacterComplexReputation(pchar,"nobility", -1); 
			DeleteAttribute(pchar, "questTemp.Wine.bottle");
			pchar.quest.Wine_Exchange.over = "yes";//снять прерывание
			pchar.quest.WineTraderQM.over = "yes";//снять прерывание
			WineTraderQMDel();
			sld = characterFromId(pchar.questTemp.Wine.id);
			sld.lifeday = 0;
			CloseQuestHeader("Wine");
			NextDiag.TempNode = "First time";
		break;
		// <-- мини-квест Дефицитный товар
		
		// Карибские нравы
		case "trial":
			iTest = FindColony(NPChar.City); // город
			QuestPointerDelLoc("portpax_town", "reload", "gate_back");
			QuestPointerDelLoc("portpax_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("portpax_fort", "reload", "reload2");
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetSquadronGoods(pchar, GOOD_BOMBS) < 2500 || GetSquadronGoods(pchar, GOOD_POWDER) < 2500)
				{
					dialog.text = "Hmm. Aber diese Ladung ist nicht voll! Wie ist das passiert?";
					link.l1 = "Verdammt! Bitte entschuldigen Sie mich, es ist meine Schuld. Ich werde sofort die fehlende Menge kaufen und Ihnen die gesamte Charge übergeben, wie wir es vereinbart haben.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Also bist du unser Kurier? Gut. Lassen wir die Dinge mit der Fracht klären, und dann erhältst du weitere Anweisungen.";
					link.l1 = "Gut.";
					link.l1.go = "trial_1";
				}
			}
			else
			{
				dialog.text = "Ich sehe dein Schiff nicht im Hafen. Schlägst du vor, die Fracht durch den Dschungel zu schleppen? Mach schnell zu unserem Hafen und komm zurück.";
				link.l1 = "Mein Schiff ist auf der anderen Seite der Insel. Ich werde es zum Hafen bringen.";
				link.l1.go = "exit";
			}
		break;
		
		case "trial_1":
			if(!bImCasual) pchar.quest.Trial_FrahtFail.over = "yes"; // belamour legendary edition если был - снять таймер
			dialog.text = "In Ordnung, Bomben und Schießpulver, jeweils 2500 Einheiten... Gut. Die Soldaten werden die Ladung entladen, deine Männer können eine Pause einlegen. Hier ist deine Bezahlung für den Frachttransport - fünftausend Pesos.";
			link.l1 = "Danke! Was sollte ich als nächstes tun? Monsieur LeCroix hat gesagt...";
			link.l1.go = "trial_2";
			DelLandQuestMark(npchar);
		break;
		
		case "trial_2":
			AddMoneyToCharacter(pchar, 5000);
			RemoveCharacterGoods(pchar, GOOD_BOMBS, 2500);
			RemoveCharacterGoods(pchar, GOOD_POWDER, 2500);
			dialog.text = "Ja, ja, du wirst jetzt deine Anweisungen erhalten. Bist du bereit, aufzupassen?";
			link.l1 = "Sicher, Offizier.";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			dialog.text = "So, our military ship 'Warlike' is cruising near the Spanish colony Porto Bello, in the southern part of the Spanish Main. This vessel is under the command of Florian Shoke, who is preparing an ambush of a Spanish heavy galleon set to leave Porto Bello in two weeks.\nThe problem is that our frigate's cannons are suffering from a casting defect, and we need to replace fifteen cannons to save the mission; otherwise, the galleon will outnumber 'Warlike' in both guns and men. \nWithout the replacement, Florian Shoke will be forced to sail away with no result. Such a sequence of events is highly undesirable. Your task is to save the mission by delivering fifteen cannons within fourteen days.";
			link.l1 = "Also, ich muss fünfzehn Kanonen an Bord nehmen, nach Portobello fahren, die Fregatte 'Militant' suchen und die Kanonen an Kapitän Florian Shoke übergeben?";
			link.l1.go = "trial_4";
		break;
		
		case "trial_4":
			dialog.text = "Genau. Du hast es richtig verstanden. Bist du bereit, diese Mission zu übernehmen?";
			link.l1 = "Wie sieht es mit der Bezahlung aus?";
			link.l1.go = "trial_5";
			link.l2 = "Es tut mir leid, Offizier, aber ich möchte einfach nicht involviert werden. Bitte entschuldigen Sie mich.";
			link.l2.go = "trial_exit";
		break;
		
		case "trial_exit":
			dialog.text = "Sie haben natürlich recht, aber ich habe auf Ihre Zustimmung gehofft. Nun muss ich einen anderen Kurier finden, obwohl mir nicht viel Zeit bleibt... Nun, ich halte Sie nicht länger auf, Kapitän.";
			link.l1 = "Mit freundlichen Grüßen.";
			link.l1.go = "trial_exit_1";
		break;
		
		case "trial_exit_1":
			DialogExit();
			AddQuestRecord("Trial", "6");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "trial_5":
			dialog.text = "Mach dir keine Sorgen darum. Florian Shoke wird dir zweihundert goldene Dublonen aus der Schatzkammer des Schiffes zahlen. Außerdem bin ich sicher, dass er dich und dein Schiff für seine eigenen Ziele nutzen möchte - natürlich mit deinem Einverständnis.";
			link.l1 = "In Ordnung, ich bin bei dieser Mission! Wo sind die Kanonen?";
			link.l1.go = "trial_6";
		break;
		
		case "trial_6":
			dialog.text = "Ich werde den Soldaten den Befehl geben, sie sofort auf euer Schiff zu laden. Setzt so schnell ihr könnt Segel, Monsieur! Viel Glück!";
			link.l1 = "Danke. Glück wird sicherlich nicht schaden, und Rückenwind auch nicht...";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			DialogExit();
			AddQuestRecord("Trial", "7");
			pchar.questTemp.Trial = "cannon";
			// belamour legendary edition
			if(!bImCasual) SetFunctionTimerCondition("Trial_CannonFail", 0, 0, 21, false); 
			else NewGameTip("Exploration mode: timer is disabled.");
			SetCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24)+15);
			if (MOD_SKILL_ENEMY_RATE >= 6)
			{
				EnemyNationHunterOnMap(true);//запуск перехватчиков
			}
			pchar.quest.Trial_cannon.win_condition.l1 = "location";
			pchar.quest.Trial_cannon.win_condition.l1.location = "Portobello";
			pchar.quest.Trial_cannon.function = "Trial_CreateFlorianFrigate";
			// Sinistra - квест "Встреча с Диего"
			bDisableFastReload = true;
			PChar.quest.VsD_GiumDyubua.win_condition.l1 = "location";
			PChar.quest.VsD_GiumDyubua.win_condition.l1.location = "PortPax_Fort";
			PChar.quest.VsD_GiumDyubua.win_condition = "VsD_GiumDyubua";
			AddMapQuestMarkShore("Shore47", false);
		break;
		
		// Опасный груз -->
		case "zpq_prs1":
			if(!isBadReputation(pchar, 70))
			{
				dialog.text = "Hm, vielleicht. Nun, aufgrund Ihres guten Rufs werde ich das Risiko eingehen, Ihnen zu vertrauen. In einem anderen Fall würde ich nicht einmal mit Ihnen darüber sprechen. Die Sache ist, dass wir eine ziemlich große Menge an spezieller Ladung benötigen, daher benötigen Sie ein großes Lastschiff und die Bereitschaft, ein Risiko einzugehen. Außerdem müssen Sie mir versprechen, niemandem davon zu erzählen.\nWenn Ihnen das peinlich ist, dann sagen Sie es mir jetzt gleich. Ich denke, ich habe meine Meinung klar gemacht...";
				link.l1 = "Klingt interessant. Ich bin dabei, wenn die Bezahlung stimmt, obwohl ich keine Ahnung habe, von welcher Ladung Sie sprechen. Sie haben trotzdem mein Wort.";
				link.l1.go = "zpq_prs2";
				link.l2 = "Ich würde nein sagen, nehme ich an... wenn ich dir mein Wort geben würde, müsste ich Arbeit verrichten, die ziemlich mühsam erscheint. Das werde ich nicht tun.";
				link.l2.go = "zpq_fld";
				notification("Reputation Check Passed", "None");
			}
			else
			{
				dialog.text = "Dein Ruf ist für mich inakzeptabel. Ich bitte dich, den Raum zu verlassen. Wir sind in der Lage, unsere Probleme selbst zu lösen.";
				link.l1 = "Wie auch immer, löse sie dann...";
				link.l1.go = "exit";
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
			}		
		break;
		
		case "zpq_fld":
			dialog.text = "Nun, zumindest hast du auf ehrliche Weise abgelehnt... Ich halte dich nicht länger auf.";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "failed";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Cumana");
		break;
		
		case "zpq_fld2":
			dialog.text = "Hm, tatsächlich hätte ich das nicht von Ihnen erwartet. Ich muss Sie bitten zu gehen... Und denken Sie an Ihr Versprechen, keine Informationen preiszugeben.";
			link.l1 = "Es tut mir leid...";
			link.l1.go = "exit";
    		ChangeCharacterComplexReputation(pchar,"nobility", -3);
			if (pchar.questTemp.zpq == "begin")
			{
				AddQuestRecord("zpq", "6");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
				CloseQuestHeader("zpq");
			}
			pchar.questTemp.zpq = "failed";
		break;
		
		case "zpq_prs2":
			dialog.text = "Prächtig. Prächtig. Das Problem ist, dass der jüngste Sturm unsere Schießpulerversorgung im Fortarsenal beschädigt hat. Ich hoffe, dass ich Ihnen nicht erklären muss, dass wir hier ein heikles Problem haben. Im Falle einer langen Belagerung wird das Fort machtlos sein. Wir werden nicht lange durchhalten.";
			link.l1 = "Jetzt verstehe ich. Welche Fracht brauchst du - und in welcher Menge?";
			link.l1.go = "zpq_prs3";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Cumana");
		break;
		
		case "zpq_prs3":
			dialog.text = "Wir brauchen 15 000 Fässer Schießpulver. Ich werde Ihnen 100 000 Pesos zahlen... Sie müssen verstehen, dass dies ein sehr guter Preis ist. Unser aktueller Zustand zwingt mich, mit solchen Kosten zu gehen, obwohl es schwierig war, den Geldbeutel des Gouverneurs davon zu überzeugen... Die Sturmsaison lässt uns unsere eigenen Versorgungswege nicht nutzen und wir wollen nicht, dass jeder von diesem Ärger erfährt...";
			link.l1 = "Ich sehe... der Preis ist wirklich nett. Du hast Risiken erwähnt...";
			link.l1.go = "zpq_prs4";
		break;
		
		case "zpq_prs4":
			dialog.text = "Ich meinte, dass eine solche große Menge Schießpulver während des Transports sehr gefährlich sein kann. Ich habe mit eigenen Augen einige Explosionen gesehen, manchmal kann ein einziger Funke ausreichen. Aber wenn du dem Sturm gegenüberstehst... Ganze Konvois halten normalerweise Abstand von der potenziellen Brandstifterin. Wenn sie explodiert, dann sind alle tot!";
			link.l1 = "Ich verstehe... Aber ich halte immer mein Wort, betrachte es als erledigt.";
			link.l1.go = "zpq_prs5";
			link.l2 = "Nun, senor... Sie haben mir solch schreckliche Dinge erzählt, dass ich jegliche Lust, diese Arbeit zu erledigen, verloren habe.";
			link.l2.go = "zpq_fld2";
		break;
		
		case "zpq_prs5":
			dialog.text = "Gut, ich bin sehr froh, dass wir einen Handel abgeschlossen haben. Ich werde dich bezahlen, sobald du mir die Fracht bringst.\nIch werde in einer Woche Geld haben, nicht früher, also nimm dir Zeit, aber ich würde dich bitten, nicht zu sehr zu zögern.";
			link.l1 = "Ich verstehe, Senor. Ich kümmere mich darum.";
			link.l1.go = "zpq_prs5_ok";
		break;
		
		case "zpq_prs5_ok":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.zpq = "begin";
			pchar.questTemp.zpq.time = 20;
			AddQuestRecord("zpq", "1");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
			SaveCurrentQuestDateParam("pchar.questTemp.zpq");
		break;
		
		case "zpq_ex":
			dialog.text = "Endlich! Ich dachte schon, du hättest unseren Handel schon vergessen. Ich werde sofort meine Soldaten befehlen, dein Schiff zu entladen. Mit Schießpulver zu arbeiten ist ein sehr heikles Geschäft, ha-ha!";
			link.l1 = "Es ist großartig, Senor, aber ich muss Sie an die Bezahlung erinnern.";
			link.l1.go = "zpq_ex2";
			RemoveCharacterGoods(pchar, GOOD_POWDER, 15000);
			AddCharacterExpToSkill(pchar, "Sailing", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 500);

            pchar.quest.zpq_sld1_fc.win_condition.l1 = "location";
            pchar.quest.zpq_sld1_fc.win_condition.l1.location = "Cumana_ExitTown";
            pchar.quest.zpq_sld1_fc.function = "zpq_sld1_fc";
		break;
		
		case "zpq_ex2":
			dialog.text = "Ja, natürlich. Sie werden 50 000 Pesos bezahlt bekommen, wie wir vereinbart haben.";
			link.l1 = "Sie machen wohl Witze, Senor?! Wir hatten einen Deal über 100 000 Pesos!";
			link.l1.go = "zpq_ex3";
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l2 = "(Vertrauenswürdig) Ich fange an zu denken, dass du mich betrügen wirst, also werde ich nicht von hier weggehen ohne meine 125 000 Pesos!";
				link.l2.go = "zpq_ex4";
			}
			link.l3 = "Hm.. Ich sehe, dass sich die Umstände geändert haben. Nun, ich sollte besser das Geld nehmen und gehen...";
			link.l3.go = "zpq_ex5";
		break;
		
		case "zpq_ex3":
			if (GetSummonSkillFromName(pchar, "Leadership") > 35)
			{
				notification("Skill Check Passed", "Leadership");
				dialog.text = "Ach, ja... Genau! 100 000 Pesos. Ich habe es vergessen, entschuldigen Sie mir. Man muss mein Alter beschuldigen, Sklerose wissen Sie... Sicher, hier sind Ihre Münzen. Es war ein Vergnügen, Geschäfte mit Ihnen zu machen, Kapitän. Jetzt tut es mir leid, aber ich habe viel Arbeit zu erledigen...";
				link.l1 = "Das Gleiche wünsche ich Ihnen, Señor. Auf Wiedersehen.";
				link.l1.go = "exit";
				pchar.questTemp.zpq = "completed";
				AddQuestRecord("zpq", "2");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
				CloseQuestHeader("zpq");
				pchar.questTemp.zpq.sum = 100000;
				AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			}
			else
			{
				notification("Skill Check Failed (36)", "Leadership");
				dialog.text = "Was?! Nimm dein Geld und verdufte, oder du wirst in dieser Kaserne verrotten!";
				link.l1 = "Du bist solch ein Lügner, senor! Ich rate dir, mir mein Geld auf gute Weise zu geben, oder ich werde die Ladung wegnehmen!";
				link.l1.go = "zpq_ex_agry";
				link.l2 = "Entschuldigung... Gut, ich nehme die Summe, die du anbietest, und dann sind wir fertig.";
				link.l2.go = "zpq_ex5";
				Log_info("Leadership skill is not sufficient");
			}
		break;
		
		case "zpq_ex4":
				dialog.text = "So eine Unverschämtheit! Ich bin nicht geisteskrank und ich erinnere mich genau, 100 000 Pesos angeboten zu haben.\n Verdammt noch mal! Ich werde deine Spielchen nicht mitspielen!";
				link.l1 = "Beruhige dich. Denke an den bereiten Brandstifter gefüllt mit Schießpulver genau vor deiner Festung. Wenn ich nur ein Wort sage, wird deine Festung zu Ruinen.";
				link.l1.go = "zpq_ex6";
		break;
		
		case "zpq_ex6":
			dialog.text = "Hm-Hm... starkes Argument. 125 000 Pesos, sagst du? Hier, nimm sie, und entschuldige mich jetzt, aber ich habe Arbeit zu erledigen...";
			link.l1 = "Auf Wiedersehen, Senor. Bis dann.";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
            AddQuestRecord("zpq", "5");
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 125000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			/*else
			{
				dialog.text = "Was?! Ich bin ein Militäroffizier! Du denkst, du könntest mir Angst machen, Bürschchen?! Wachen, nehmt "+GetSexPhrase("ihn","sie")+"!";
				link.l1 = "Viel Glück beim Versuchen, Ratten der Kerkern...";
				link.l1.go = "zpq_ex_war";
			}*/
		break;
		
		case "zpq_ex5":
			dialog.text = "Hervorragend! Sie haben die richtige Wahl getroffen. Nehmen Sie Ihre Münzen und auf Wiedersehen. Es war mir ein Vergnügen!";
			link.l1 = "Auf Wiedersehen...";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
            AddQuestRecord("zpq", "3");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 50000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
		break;
		
		case "zpq_ex_agry":
			dialog.text = "Ach du Schuft! Wachen, nehmt "+GetSexPhrase("ihn","sie")+"!";
			link.l1 = "Argh! Es scheint, dass ich mein Geld von deinem leblosen Körper nehmen muss...";
			link.l1.go = "zpq_ex_war";
		break;
		
        case "zpq_ex_war":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetFightMode(PChar, true);
			pchar.questTemp.zpq = "failed";
            AddQuestRecord("zpq", "4");
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 100000;
			AddMoneyToCharacter(npchar, makeint(sti(pchar.questTemp.zpq.sum)*2 + rand(5000)));
			GiveItem2Character(npchar, "blade_21");
			EquipCharacterbyItem(npchar, "blade_21");
			npchar.SaveItemsForDead  = true;
			npchar.DontClearDead = true;
			npchar.cirassId = Items_FindItemIdx("cirass3");
			chrDisableReloadToLocation = true;
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			LAi_group_SetCheck(slai_group, "OpenTheDoors");
			AddSimpleRumour("Such terrible things happen here! They say that some prisoner has escaped from the casemates! He slaughtered all the guards, stole the treasury, and just went away! Wow!", SPAIN, 5, 1);
		break;
		// <-- Опасный груз
	}
}

void GetGunType()
{
	int iGunType;
	if(makeint(pchar.rank) < 6) iGunType = rand(1);	//18&&24
	if(makeint(pchar.rank) >= 6 && makeint(pchar.rank) < 15) iGunType = rand(2); //24&&32	
	if(makeint(pchar.rank) >= 15 && makeint(pchar.rank) < 24) iGunType = rand(2)+2; //32&&36&&42
	if(makeint(pchar.rank) >= 24) iGunType = 5-rand(1); //36clv&&42
	int iAdd = makeint(GetSummonSkillFromName(pchar, SKILL_COMMERCE)/20);
	
	switch (iGunType)
	{
		case 0:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_24;     					
			pchar.questTemp.PrisonGun.Price = 28 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*5+25+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "24 calibre cannons";
		break; 
		case 1:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_18;     					
			pchar.questTemp.PrisonGun.Price = 25 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*5+25+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "couleuvrines";
		break; 
		case 2:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_32;     					
			pchar.questTemp.PrisonGun.Price = 32 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*3+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "32 calibre cannons";
		break; 
		case 3:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_36;     					
			pchar.questTemp.PrisonGun.Price = 36 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*3+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "36 calibre cannons";
		break;
		case 4:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_36;     					
			pchar.questTemp.PrisonGun.Price = 49 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "full couleuvrines";
		break; 
		case 5:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_42;     					
			pchar.questTemp.PrisonGun.Price = 40 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)+20+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "42 calibre cannons";
		break; 
	}
}
