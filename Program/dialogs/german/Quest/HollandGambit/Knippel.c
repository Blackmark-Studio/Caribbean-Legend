// Чарли Книппель - старый артиллерист
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, iTemp, amount;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		//ветка на взятие 2 варианта прохождения - за Англию
		if(CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Eng") && !CheckAttribute(npchar, "quest.HWICTake") && !CheckAttribute(pchar, "questTemp.HWIC.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
		{
			dialog.text = "Ahoi Kamerad, Kettenkugel in meinem Hintern! Was führt dich hierher?";
			link.l1 = "Kettenkugel deine...was? Ach, egal, wollte nur hallo sagen.";
			link.l1.go = "exit";
			link.l2 = "Grüße, Herr Knippel. Ha, ich sehe, warum sie dich Knippel nennen. Es gibt Gerüchte, dass du früher bei der englischen Marine gedient hast. Ich habe ein gutes Schiff und eine geschickte Mannschaft. Ich möchte mich und mein Schiff in den Dienst der englischen Krone... äh... Commonwealth stellen. Können Sie mir einen Rat geben oder mich jemandem empfehlen oder mir vielleicht in dieser Angelegenheit helfen?";
			link.l2.go = "Knippel_check";
			break;
		}
		//за Голландию
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "toKnippel")
			{
				dialog.text = "Ahoymatey, Kettenkugel mein Hintern! Was bringt dich hierher?";
				link.l1 = "Grüße, Herr Knippel. Ha, ich sehe, warum man dich Knippel nennt. Es gibt Gerüchte, dass du früher in der englischen Marine gedient hast, deshalb möchte ich dich um Hilfe bitten...";
				link.l1.go = "Dominica";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Kettenkugel meinen Arsch! Was willst du, Kumpel?";
			link.l1 = "Nein, es ist nichts. Ich gehe.";
			link.l1.go = "exit";
			break;
		}
		//за Англию
		if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
		{
			if (pchar.questTemp.HWIC.Eng == "TakeHollConvoy")
			{
				dialog.text = "Ahoi Käpt'n, ich habe Gerüchte gehört, dass ein Silberkonvoi abgefangen wurde...";
				link.l1 = "Sie sind gut informiert, Herr Knippel.";
				link.l1.go = "HollConvoy_Check";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SentJons");
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "Wait")
			{
				dialog.text = "Fragen, Käpt'n?";
				link.l1 = "Nein, es ist nichts. Ich gehe.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "Start_main")
			{
				dialog.text = "Es freut mich, Sie zu sehen, Käpt'n! Mein Kommandant Richard Fleetwood wollte selbst hierher kommen, um Sie kennenzulernen, aber gestern Abend ist ein Unfall passiert... Jemand versuchte, ihn mitten auf der Straße zu töten, Kettenkugel mein Arsch!";
				link.l1 = "Unmöglich! Was haben die Wachen gemacht?";
				link.l1.go = "Fleetwood_house";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Fragen, Käpt'n?";
			link.l1 = "Nein, es ist nichts. Ich gehe.";
			link.l1.go = "exit";
		break;
		}
			dialog.text = "Ahoi Kamerad, Kettenkugel mein Hintern! Was hat dich hierher gebracht?";
			link.l1 = "Hallo, ich schaue nur vorbei.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------за Голландию--------------------------------------------------	
		case "Dominica":
			dialog.text = "Ahoi, wirklich? Und wie kann ein alter Seemann, der schon lange gestrandet ist, dir helfen, Kumpel?";
			link.l1 = "Sieh... Ich bin nur ein gewöhnlicher Kapitän und ich mache regelmäßige Reisen zwischen Martinique und Curacao. Also wurde ich zweimal von dem Geisterschiff nicht weit von Martinique angegriffen... Aber hier ist die Sache, sie ist keine Fata Morgana oder Fliegender Holländer. Ich konnte ihre Segel mit einfachen Kanonenkugeln zerreißen!";
			link.l1.go = "Dominica_1";			
		break;
		
		case "Dominica_1":
			dialog.text = "So ist es also? Es ist sicherlich ungewöhnlich für ein Geisterschiff, Segeltuch durch einen soliden Schuss zu verlieren, bei mir Zittern die Balken...";
			link.l1 = "Wir haben nur überlebt, weil mein Schiff es beim Segeln hart am Wind überholen konnte. Beim letzten Mal musste ich meine ganze Ladung über Bord werfen, um meinen Rumpf genug zu entlasten und zu entkommen... kannst du dir den Verlust vorstellen? Es ist herzzerreißend!";
			link.l1.go = "Dominica_2";			
		break;
		
		case "Dominica_2":
			dialog.text = "Verdammt noch mal, Kap'n...";
			link.l1 = "Mathias Beck, der Gouverneur von Curacao, hat meine Beschwerden einfach beiseite gewischt. Er sagte, dass die Geschichten vom Geisterschiff Unsinn sind und meine Wächter betrunken von Grog waren. Der Gouverneur von Martinique versprach, eine Patrouille dorthin zu schicken, aber seine Augen sagten mir, dass er sich nicht die Mühe machen kann, irgendetwas zu tun. Ich kann nicht nach Martinique zurückkehren, während dieser verdammte Piratengeist herumschleicht. Mein Schiff ist klein, ebenso wie meine Besatzung, es ist wahrscheinlich, dass wir die dritte Begegnung mit ihm nicht überleben...";
			link.l1.go = "Dominica_3";			
		break;
		
		case "Dominica_3":
			dialog.text = "Es ist eine verdammte Schande, Kamerad. Aber wie kann ich dir helfen?";
			link.l1 = "Ich habe von den Seemännern hier gehört, dass es in St. John's einen Kapitän namens Richard Fleetwood gibt, der dasselbe Geisterschiff gejagt hat. Ich kenne ihn nicht persönlich, deshalb erzähle ich Ihnen diese Geschichte, vielleicht könnten Sie ihm die Geschichte von meinen Unglücken weitergeben? Ich bin sicher, dass der dreckige Pirat irgendwo in der Nähe der wilden Küsten von Dominica versteckt ist und zwischen Barbados und Martinique plündert.";
			link.l1.go = "Dominica_4";			
		break;
		
		case "Dominica_4":
			dialog.text = "Zwischen Barbados und Martinique? Ya har! Eine fette und reiche Handelsroute. Das klingt sehr nach etwas, was diese Wasserratte tun würde.";
			link.l1 = "Ich bin weder reich noch fett und habe kein Geld, um einen Marinekapitän für eine militärische Eskorte zu bestechen. Aber wenn Sir Fleetwood bereits auf der Suche nach diesem Schiffsratte ist, könnten Sie ihm bitte sagen, wo er diesen 'Fliegenden Holländer' finden könnte?";
			link.l1.go = "Dominica_5";			
		break;
		
		case "Dominica_5":
			dialog.text = "Du hast gut daran getan, hierher zu kommen, Kamerad. Ich werde deine Geschichte den richtigen Männern erzählen, bei meiner Leber! Bald wirst du wieder mit Martinique handeln können.";
			link.l1 = "Ich hoffe, dass Gott Ihre Worte hören wird! Danke, dass Sie mir zugehört haben, Charlie. Ich hoffe wirklich auf das Beste. Lebewohl und weiche der Kettenschuss aus!";
			link.l1.go = "Dominica_6";			
		break;
		
		case "Dominica_6":
			DialogExit();	
			pchar.questTemp.HWIC.Holl = "toDominica";
			AddQuestRecord("Holl_Gambit", "1-17");
			pchar.quest.toDominica.win_condition.l1 = "location";
			pchar.quest.toDominica.win_condition.l1.location = "Dominica";
			pchar.quest.toDominica.function = "PrepareToFleetwoodAttack";
			DelMapQuestMarkShore("Shore1");
			DelMapQuestMarkShore("Shore2");
			AddMapQuestMarkIsland("Dominica", true);
		break;

//----------------------------------------------за Англию--------------------------------------------------	
		case "Knippel_check"://начинаем проверять нашего ГГ по всем статьям
			if(makeint(PChar.reputation.nobility) < 48)//низкая репа
			{
				// belamour legendary edition покажем критерии
				notification("Reputation Too Low! (Adventurer)", "None");
				PlaySound("Voice\English\hambit\Charlie Knippel-04.wav");
				dialog.text = "Frohes altes England braucht keine Dienste von Schurken, Kettenkugel meinen Arsch! Respektvoll können Sie sich direkt verpissen.";
				link.l1 = "He, he, Kumpel, hüte deine Zunge, sonst nähe ich sie zu!";
				link.l1.go = "exit";
				break;
			}
			else
			{
				notification("Reputation Check Passed", "None");
			}
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 30)//низкая навигация
			{
				dialog.text = "Kapitän, ich werde direkt sein. Sie könnten Ihren Weg aus einem nassen Sack nicht segeln. Kommen Sie zurück, wenn Sie mehr Fähigkeiten im Navigieren haben, kapieren?";
				// belamour legendary edition покажем критерии  -->
				notification("Skill Check Failed (30)", SKILL_SAILING);
				//<--
				dialog.text = "Cao'n, unsere Flotte braucht erfahrene Kapitäne, keine Landratten. Komm zurück, wenn du die Kunst der Navigation gemeistert hast.";							 
				link.l1 = "Ich verstehe... Dann werde ich dich später sehen.";
				link.l1.go = "exit";
				break;
			}
			else
			{
				notification("Skill Check Passed", SKILL_SAILING);
			}
			dialog.text = "Ahoi, du bist gerade rechtzeitig, Kapitän, schusselt mich in den Hintern! Richard wusste nicht, auf wen er sich bei diesem riskanten Geschäft verlassen konnte, er dachte sogar daran, es abzulehnen... Also singen die kleinen Vögel der Gelegenheit heute süß in deinen Ohren. Wenn du unseren Standards entsprichst, werde ich dich einem sehr wichtigen Mann empfehlen. Hast du genug Schrot in deinem Codpiece, um damit umzugehen?";
			link.l1 = "Ich bin mit Traubenhagel geladen, Herr Knippel.";
			link.l1.go = "Knippel_task";
		break;
		
		case "Knippel_task"://первое задание
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Bridgetown_tavernkeeper"));
			DelLandQuestMark(characterFromId("Lucas"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Ar har! Ich sehe, dein Hahn steht, Kapitän! Bald wird Feuer flackern! Nun hör genau zu. Die Silberflotte der Niederländischen Westindischen Kompanie hat Willemstad auf Curaçao vor ein oder zwei Tagen verlassen. Sie segelt nach Philipsburg. Dieses Mal sind nur wenige Schiffe in der Flotte. Ein einzelnes Galeone mit dem Silber im Frachtraum und zwei Eskorten. Fang die Silberflotte ab, erobere das Galeone mit der Silberladung und bringe sie nach Antigua. Die Eskorten kannst du jedoch versenken, sie sind entbehrlich. Schieß ihnen die Lebern mit Kettenkugeln durch, yar!";
			link.l1 = "Ihre Tage sind gezählt.";
			link.l1.go = "Knippel_task_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Knippel_task_1":
			dialog.text = "Ein Ratschlag, Kapitän. Die Handelsroute von Curacao nach Sint Maarten liegt nicht weit von den Ufern von St. Christopher. Ich würde raten, dort einen Hinterhalt vorzubereiten. Bereiten Sie sich und Ihr Schiff gut auf diese Auseinandersetzung vor. Mit der Westindischen Kompanie aneinanderzugeraten, ist kein Spaziergang im Park mit einem hübschen Mädchen.";
			link.l1 = "Ich weiß, worauf ich mich einlasse, aber ich schätze Ihre Offenheit, Herr Knippel. Ich komme mit dem holländischen Silber zurück.";
			link.l1.go = "Knippel_task_2";			
		break;
		
		case "Knippel_task_2":
			DialogExit();
			npchar.quest.HWICTake = "true";
			pchar.questTemp.HWIC.CanTake.Eng = "true";//признак, что английка уже бралась
			HWICSilverConvoyInWorld();
			AddQuestRecord("Holl_Gambit", "2-1");
			ReOpenQuestHeader("Holl_Gambit"); // данила ,чтобы вышел из архива. 																				   
			pchar.questTemp.HWIC.Eng = "begin";
			SetFunctionTimerCondition("HollConvoy_Over", 0, 0, 15, false);
		break;
		
		case "HollConvoy_Check"://начинаем проверять
			int iHal = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_GALEON_L) iHal++;
				}
			}//признак наличия ТГ в компаньонах
			if (iHal > 0)
			{
				amount = sti(pchar.questTemp.HWIC.Eng.SlvQty) - GetSquadronGoods(pchar, GOOD_SILVER);
				if (amount <= 0)
				{
					dialog.text = "Es ist nicht nötig, mir zu erzählen, was passiert ist, Käpt'n. Ich wurde über alles informiert, während der Zollbeamte Ihr Schiff inspizierte... Sie haben es ziemlich gut gemacht, Käpt'n. Ausgezeichnet! Es klang nicht einfach, Kettenkugel mein Hintern!";
					link.l1 = "Es ist schön, geschätzt zu werden.";
					link.l1.go = "HollConvoy_complete";
				}
				else
				{
					dialog.text = "Keine Notwendigkeit, mir zu erzählen, was passiert ist, Kumpel. Ich wurde über alles informiert, während der Zollbeamte Ihr Schiff inspizierte... Sie haben es versäumt, das gesamte Silber zurückzubringen, Kettenkugel mein Hintern! Ich weiß genau, wie viel Silber auf diesem Ostindienmann bis auf den letzten Peso war. Der Zweck dieser Mission war nicht nur, Ihre Kampffähigkeiten zu testen, sondern auch Ihre Ehrlichkeit. Sie haben letzteres nicht bestanden. Raus aus meinem Haus, Leichtmatrose!";
					link.l1 = "Zum Teufel mit dir dann, Einfaltspinsel!";
					link.l1.go = "HollConvoy_fail";
				}
			}
			else
			{
				dialog.text = "Ahoi, Kumpel. Ich sehe die niederländische Ostindienfahrer nicht in deinem Geschwader. Ich habe dir gesagt, du sollst sie als Preis hierher bringen. Du hast sie verkauft und versucht, das Geld für dich zu behalten, hm?";
				link.l1 = "Warte, ich sollte das Schiff bringen? Ich dachte, du wolltest nur das Silber.";
				link.l1.go = "HollConvoy_noShip";
			}
		break;
		
		case "HollConvoy_noShip":
			dialog.text = "Niemand hält Charlie Knippel für einen Narren, Kumpel! Ich erinnere mich genau daran, was ich dir gesagt habe und was nicht. Du hast die Bedingungen unseres Handels gebrochen und kein ehrlicher Engländer wird mit dir arbeiten, hier gibt es keinen Platz für Schurken. Raus aus meinem Haus, Seebär!";
			link.l1 = "Zum Teufel mit dir dann, Einfaltspinsel!";
			link.l1.go = "HollConvoy_fail";
		break;
		
		case "HollConvoy_fail":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-3");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Eng");//зачищаем для возможности отката к голландскому варианту
			pchar.questTemp.HWIC.Fail2 = "true";
		break;
		
		case "HollConvoy_complete":
			dialog.text = "Besuchen Sie mich morgen und ich werde Sie meinem Mäzen vorstellen. Er wird Ihnen eine Arbeit anbieten, die Ihrer Fähigkeiten würdig ist. Zudem wird er für Ihre...finanziellen Anreize sorgen. Leinen los!";
			link.l1 = "Sehr gut, Herr Knippel. Ich werde morgen hier sein.";
			link.l1.go = "exit";
			npchar.greeting = "knippel_2";
			AddDialogExitQuestFunction("HollConvoy_Remove");
			AddQuestRecord("Holl_Gambit", "2-4");
			SetTimerFunction("EnglandGambit_2_ZadanieStart", 0, 0, 1);
			pchar.questTemp.HWIC.Eng = "Wait";
			AddSimpleRumourCity("They say that you captured a Dutch ship filled with silver. Well done! You are a valiant sailor, captain! Godspeed!", "SentJons", 10, 3, "");
		break;
		
		case "Fleetwood_house":
			dialog.text = "Ich habe mir dieselbe Frage gestellt... Irgendein Bastard hat gemahlenen Pfeffer in die Augen von Kapitän Fleetwood geworfen und ihn in die Brust gestochen, bevor Richard überhaupt sein Schwert greifen konnte. Der Mörder hoffte, den Kapitän mit einem einzigen Stich zu erledigen, da er keine Zeit für einen weiteren hatte, aber er scheiterte. Kapitän Fleetwood trägt immer eine Kürass unter seinem Mantel\nDer verdammte Abschaum, seine Leber mit Kettenkugeln zerschossen, konnte fliehen und sich verkriechen. Es sieht so aus, als hätte er Freunde in der Stadt. Das einzige Detail, an das sich der Kapitän erinnert, ist, dass der Attentäter nur ein Auge hat. Es wird uns jedoch nicht viel helfen, es gibt viele von diesen Zyklopen, die heutzutage die Docks durchstreifen\nRichard hat viel Blut verloren und der Pfeffer hat seine Augen so schlimm gereizt, dass er jetzt fast blind ist...";
			link.l1 = "Gemahlener Pfeffer? Das ist ein teurer Weg, jemanden zu blenden. Fleetwood muss jemanden wirklich verärgert haben. Es tut mir leid um deinen Kapitän. Hat die Suche nach dem Angreifer etwas ergeben?";
			link.l1.go = "Fleetwood_house_1";
		break;
		
		case "Fleetwood_house_1":
			dialog.text = "Cap'n Fleetwoods Marineinfanteristen haben die ganze Stadt und die örtlichen Buchten durchsucht, aber sie haben nichts gefunden, Kettenkugeln ihren Hälsen! Wenn wir ihn gleich nach dem Angriff nicht gefunden haben, gibt es jetzt keine Hoffnung, den Bastard zu finden. Cap'n Fleetwood hat viele Feinde... Aber, Cap'n, mein Kommandant möchte Sie trotzdem sehen, trotz des Unfalls. Er ruht jetzt in seinem Haus, also gehen wir zu ihm. Folgen Sie mir!";
			link.l1 = "Führen Sie weiter, Herr Knippel.";
			link.l1.go = "Fleetwood_house_2";
		break;
		
		case "Fleetwood_house_2":
			chrDisableReloadToLocation = true;//закрыть локацию
			bDisableFastReload = true;//закроем быстрый переход
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", true);//чтобы не сбежал
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_town", "reload", "houseH1", "OpenTheDoors", -1);
			pchar.quest.Knippel_Outside.win_condition.l1 = "location";
			pchar.quest.Knippel_Outside.win_condition.l1.location = "SentJons_town";
			pchar.quest.Knippel_Outside.function = "Knippel_GoTown";
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);
			sld = characterFromId("Fleetwood");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseSP3_room", "goto", "goto1");
			AddLandQuestMark(sld, "questmarkmain");
			pchar.GenQuestBox.SentJons_houseSP3_room = true;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.money = 110000;
		break;
		
		case "InFleetwoodHouse":
			dialog.text = "Cap'n Fleetwood ist oben in seinem Zimmer. Geh zu ihm, er wartet auf dich. Ich bleibe hier.";
			link.l1 = "Verstanden, Herr Knippel. Ich bin unterwegs.";
			link.l1.go = "exit";	
		break;
		
		case "Knippel_ToOfficer":
			dialog.text = "Hören Sie zu, Kapitän... Kapitän Fleetwood ist sicher und in guten Händen. Ich möchte Ihnen helfen, Rache an dem Bastard zu nehmen, der ihn angegriffen hat. Ich biete Ihnen meine Dienste als Artillerieoffizier an. Ich bin nicht so gut im Fechten, dafür bin ich zu alt, aber ich kann die Topsegel eines Handelsschiffs auf tausend Schritte Entfernung abschießen.";
			link.l1 = "Das würde ich gerne sehen. Willkommen an Bord, Herr Knippel!";
			link.l1.go = "Knippel_ToOfficer_1";	
		break;
		
		case "Knippel_ToOfficer_1":
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", false);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", false);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", false);//откроем локаторы
			//Книппеля - в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;//полубессмертен
			npchar.loyality = 20;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			SetFunctionTimerCondition("GotoBridgetownOver", 0, 0, 30, false);//на все дела - 1 месяц
			AddSimpleRumourCity("They say that Sir Richard Fleetwood himself is indebted in you. You are a very important man in our town, sir", "SentJons", 10, 3, "");
		break;
		
		case "hired":
			dialog.text = "Ahoi Käpt'n! Brauchst du etwas?";
			link.l1 = "Nein, nichts.";
			link.l1.go = "exit";
			NextDiag.TempNode = "hired";
		break;
		
		case "MC_GoAway":
			PlaySound("Voice\English\hambit\Charlie Knippel-07.wav");
			if (pchar.questTemp.HWIC.Eng == "MirageFail")
			{
				dialog.text = "Du bist ein kompletter Trottel, Kumpel, Kugelhagel mein Hintern! Du hast versagt, eine elementare Aufgabe zu erfüllen - die 'Mirage' einzufangen, ohne die 'Walküre' zu verlieren\nUnsere Crew wird nicht länger unter deinem Kommando dienen. Wir sind sicher, dass Sir Fleetwood unsere Entscheidung gutheißen wird, er mag Idioten genauso wenig wie wir.";
				link.l1 = "Fick dich und deinen Meister!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "GotoBridgetown" || pchar.questTemp.HWIC.Eng == "SeekVanBerg")
			{
				dialog.text = "Du bist ein kompletter Idiot, Kumpel, Kettenkugel mein Hintern! Wir haben zu viel Zeit damit verschwendet, deine persönlichen Probleme zu lösen\nUnsere Crew wird dir nicht länger dienen. Wir sind sicher, dass Sir Fleetwood unsere Entscheidung billigen wird, er mag Idioten genauso wenig wie wir.";
				link.l1 = "Fick dich und deinen Meister!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "VanBergFailInWorld")
			{
				dialog.text = "Du bist ein kompletter Idiot, Kumpel, Kettenkugel in meinem Arsch! Dir wurde gesagt, du sollst einen einsamen Händler auf der 'Walküre' spielen, und was hast du gemacht? Du hast den Piraten mit deiner Flottille verängstigt!\nWir sind sicher, dass Sir Fleetwood unsere Entscheidung gutheißen wird, er mag Idioten genauso wenig wie wir.";
				link.l1 = "Fick dich und deinen Meister!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "MirageTake")
			{
				dialog.text = "Du bist ein kompletter Idiot, Kumpel, Kettenkugel mein Arsch! Hast du beschlossen, unsere Zeit mit allem anderen als der Eroberung der 'Mirage' und der Fahrt nach Antigua zu verschwenden?\nUnsere Crew wird dir nicht länger dienen. Wir sind sicher, dass Sir Fleetwood unsere Entscheidung gutheißen wird, er mag Idioten genauso wenig wie wir.";
			link.l1 = "Fick dich und deinen Meister!";
			link.l1.go = "exit";
			}
			PChar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_VALCIRIA)//если сам на Валькирии
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
				pchar.Ship.name = "Boat";
				SetBaseShipData(pchar);
				SetCrewQuantityOverMax(PChar, 0);
			}
			else
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA)
						{
							pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Eng.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			ChangeCharacterAddressGroup(npchar, "SentJons_houseH1", "goto", "goto1");//Книппеля домой
			pchar.questTemp.HWIC.Eng = "end";
			pchar.questTemp.HWIC.Detector = "eng_fail";
			CloseQuestHeader("Holl_Gambit");
		break;
		
		case "OnCuracao":
			pchar.quest.HWICEng_toBarbadosOver.over = "yes";//снять прерывание
			dialog.text = "Grüße, Käpt'n. Schön dich zu sehen!";
			link.l1 = "Grüße, Herr Knippel. Haben Sie das Geld? Geben Sie es mir und wir gehen nach Willemstad, um Abigail zu holen. Werden Sie mich begleiten?";
			link.l1.go = "OnCuracao_1";	
		break;
		
		case "OnCuracao_1":
			dialog.text = "Kap'n, hör zu... Es gibt jetzt keinen Grund, irgendwohin zu gehen.";
			link.l1 = "Wovon redest du? Das ist Unsinn!";
			link.l1.go = "OnCuracao_2";	
		break;
		
		case "OnCuracao_2":
			dialog.text = "Ich habe einen Brief von Kapitän Fleetwood für Sie. Und das Geld. Aber dieses Geld ist nicht für Abigails Vater, sondern für Sie. Zweihunderttausend Pesos. Lesen Sie den Brief und versuchen Sie, ihn nicht zu hart zu beurteilen...";
			link.l1 = "Was zum Teufel geht hier vor sich?! Noch eine unangenehme Überraschung? Gib mir den Brief!";
			link.l1.go = "OnCuracao_3";	
		break;
		
		case "OnCuracao_3":
			DialogExit();
			NextDiag.CurrentNode = "OnCuracao_4";
			AddMoneyToCharacter(pchar, 200000);
			LAi_SetCitizenType(npchar);
			npchar.lifeday = 1;//еще денек пусть погуляет по пляжу
			pchar.quest.Holland_ShoreAttack.win_condition.l1 = "location";
			pchar.quest.Holland_ShoreAttack.win_condition.l1.location = "Curacao";
			pchar.quest.Holland_ShoreAttack.function = "CreateHollandShorePatrol";//патруль в прибрежных водах
			LocatorReloadEnterDisable("SentJons_town", "basement1_back", false);//открыть подземелье
			pchar.questTemp.HWIC.Eng = "MerdokMeeteng";
			AddQuestRecordInfo("LetterFromFleetwood", "1");
			AddQuestRecord("Holl_Gambit", "2-23");
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "OnCuracao_4":
			dialog.text = "Hast du es gelesen, Käpt'n? Ich werde ehrlich sein. Ich schäme mich für Käpt'n Fleetwood und das, was er getan hat, seine... ach, verdammt. Rodenburg war wütend, als er von Abigails Romanze mit Richard erfuhr. Fußpatrouillen durchkämmen Curacao und es kreuzen Kriegsschiffe der Kompanie in den lokalen Gewässern. Wir müssen hier verdammt noch mal raus.\nKapitän, brauchst du einen Kanonier? Ich brauche keinen Luxus - nur eine normale Seeration auf regelmäßiger Basis. Ich bin nicht so gut im Fechten, dafür bin ich zu alt, aber ich kann die Topsegel eines Handelsschiffs auf tausend Schritte abknallen.";
			link.l1 = "Nun verdammt, ich würde gerne sehen, wie du das schaffst, Herr Knippel. Willkommen in der Mannschaft!";
			link.l1.go = "Knippel_hire";
			link.l2 = "Es tut mir leid, dass ich euch englischen Schurken überhaupt geholfen habe. Ich weiß jetzt nicht, wie ich aus diesem Schlamassel herauskommen soll. Geh deinen eigenen Weg, ich habe genug von Überraschungen.";
			link.l2.go = "Knippel_exit";
			DelLandQuestMark(npchar);
		break;
		
		case "Knippel_hire":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*200;
			npchar.OfficerWantToGo.DontGo = true;
			DeleteAttribute(npchar, "CompanionDisable");//теперь можем и в компаньоны
			DeleteAttribute(npchar, "HalfImmortal");
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 120, 120);
			LAi_SetOfficerType(npchar);
			npchar.greeting = "knippel_hire";
			NextDiag.CurrentNode = "Knippel_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			
			//Sinistra - через 2 месяца стартует личный квест Чарли Книппеля "Длинные тени старых грехов"
			SetTimerCondition("DTSG_Start", 0, 0, 60, false);
		break;
		
		case "Knippel_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
		break;
		
//------------------------------------------------против всех-----------------------------------------------
		case "Knippel_abordage":
			dialog.text = "Avast du Bilgeratte! Warum hast du dieses friedliche holländische Schiff angegriffen? Ich habe keine wertvollen Waren oder Gold, verdammt noch mal!";
			link.l1 = "Holländisches Schiff? Haha! Bring mich nicht zum Lachen, 'Holländer'. Ich habe deine Brigantine angegriffen, um dich zu fangen, lieber Charlie. Willkommen in meinem Laderaum. Wir werden ein Gespräch darüber führen, wohin du segelst und warum...";
			link.l1.go = "Knippel_abordage_1";	
		break;
		
		case "Knippel_abordage_1":
			AddQuestRecord("Holl_Gambit", "3-20");
            pchar.quest.Knippel_DieHard.over = "yes";
		    DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
            DialogExit();
			LAi_SetPlayerType(pchar);
			pchar.questTemp.HWIC.Self = "KnippelPrisoner";
			npchar.lifeday = 0;
			SetFunctionTimerCondition("RemoveKnippelOver", 0, 0, 1, false);//таймер до конца суток, ибо нефиг
		break;
		
		case "Knippel_prisoner":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\hambit\Charlie Knippel-07.wav");
			dialog.text = "Du bist ein Teufel, Pirat... Du wirst in der Hölle brennen für all deine Sünden! Schrei...";
			link.l1 = "Entspannen Sie sich, Prediger. Du predigst wie ein Puritaner. Du solltest dich besser um den Zustand deiner Seele kümmern.";
			link.l1.go = "Knippel_prisoner_1";
		break;
		
		case "Knippel_prisoner_1":
			dialog.text = "Was planen Sie, Schurke? Was wollen Sie von meinem Kommandanten und von dem armen holländischen Mädchen?";
			link.l1 = "Das geht dich nichts an, Charlie. Ich brauche dich nicht mehr. Steh auf.";
			link.l1.go = "Knippel_prisoner_2";	
		break;
		
		case "Knippel_prisoner_2":
			dialog.text = "Willst du mich töten? Würdig für so einen Bastard wie dich. *spuckt* Fick dich!";
			link.l1 = "Steh auf, Charlie. Sprich dein letztes Gebet.";
			link.l1.go = "Knippel_prisoner_3";	
		break;
		
		case "Knippel_prisoner_3":
			DialogExit();
			LAi_SetActorType(pchar);
			sld = characterFromId("KnippelClone");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Ground_StandUp", "Kill_Knippel", 3.5);
			pchar.quest.RemoveKnippelOver.over = "yes";//снять таймер
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Knippel_officer":
			dialog.text = "Ahoi Käpt'n, Kettenschuss mein Hintern!";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Herr Knippel, ich gehe in die alte verlorene indische Stadt Tayasal. Ich werde klar sein, dies wird eine wirklich gefährliche Reise sein und es ist auch eine ungewöhnliche - wir müssen dorthin durch dieses...magische Idol kommen. Werden Sie sich mir anschließen?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Herr Knippel, geben Sie mir einen vollständigen Schiffsbericht.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Ich möchte, dass Sie bestimmte Waren kaufen, jedes Mal wenn wir angedockt sind.";
				Link.l12.go = "QMASTER_2";
			}
			
			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Ich bin auf Ihren Befehl hier, Kapitän.";
				Link.l2 = "Ich muss dir mehrere Befehle geben.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "Knippel_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Hör auf meine Befehle!";
            Link.l1.go = "stay_follow";
			link.l2 = "Es ist nichts. Entlassen!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Knippel_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Verdammt... Die Kanonen sind in Ordnung, wir ersetzen die, die explodieren, und halten unser Pulver trocken und sicher. Was für einen Bericht haben Sie erwartet, Kapitän? Ich bin ein alter Kanonier, kein Zahlmeister. Kettenkugel mein Hintern, ich bin jedoch der beste Kanonier in der Karibik, merken Sie sich das!";
			Link.l1 = "Kein Streit hier, Herr Knippel, Sie kennen Ihr Handwerk. Ich werde selbst einen Zahlmeister finden, machen Sie sich keine Sorgen.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Sie wollen, dass der alte Charlie sein Geschützdeck gegen das Achterdeck tauscht? Kapitän, ich versenke Schiffe, kämpfe aber nicht um jeden Peso. Und ich bin mir sicher, dass sie mich in der allerersten Kolonie, in der wir das versuchen, über den Tisch ziehen werden.";
			link.l1 = "Aber natürlich, Herr Knippel. Ich sollte anfangen, einen passenden Zahlmeister zu suchen.";
			link.l1.go = "exit";
		break;
		
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Ich höre Ihnen zu.";
			Link.l1 = "Es geht ums Entern.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Es geht um dein Schiff.";
			Link.l2.go = "Companion_TaskChange";
			if (bBettaTestMode) // Только при бета-тесте
			{
				Link.l3 = "Ich möchte, dass du für eine Weile meine Staffel verlässt und dein Glück auf eigene Faust suchst.";
				Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "Bisher nichts.";
			Link.l8.go = "exit";
			break;

		case "Companion_TaskBoarding":
			dialog.Text = "Also, was ist dein Wunsch.";
			Link.l1 = "Entern Sie keine feindlichen Schiffe. Kümmern Sie sich um sich selbst und die Besatzung.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Ich möchte, dass du feindliche Schiffe entern.";
			Link.l2.go = "Companion_TaskBoardingYes";
			break;

		case "Companion_TaskChange":
			dialog.Text = "Also, was ist dein Wunsch.";
			Link.l1 = "Ich möchte, dass Sie Ihr Schiff nach dem Entern nicht gegen ein anderes eintauschen. Ihr Schiff ist zu wertvoll.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Wenn du feindliche Schiffe entern, kannst du sie für dich selbst nehmen, falls sie zufällig anständig sind.";
			Link.l2.go = "Companion_TaskChangeYes";
			break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Jawohl!";
			Link.l1 = "Ruhig.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
			break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "Es wird erledigt sein.";
			Link.l1 = "Ruhig.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
			break;

		case "Companion_TaskChangeNo":
			dialog.Text = "Jawohl!";
			Link.l1 = "Es wird erledigt sein.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
			break;

		case "Companion_TaskChangeYes":
			dialog.Text = "Es wird erledigt sein.";
			Link.l1 = "Ruhig.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
			break;
			//	<========////////////////////////////////////////

		case "stay_follow":
            dialog.Text = "Befehle?";
            Link.l1 = "Steh hier!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Folge mir und halte Schritt!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Ändern Sie die Art der Munition für Ihre Feuerwaffen.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Wählen Sie die Art der Munition:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Es gibt eine Änderung der Disposition!";
            Link.l1 = "Entlassen.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Es gibt eine Änderung der Gesinnung!";
            Link.l1 = "Entlassen.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Ich habe während meines Dienstes wirklich an dich gewöhnt, "+pchar.name+", und ich lasse meinen Käpt'n nicht im Stich. Ich würde dir durch die Hölle folgen, wenn es sein muss. Ich bin bei dir!";
			link.l1 = "Danke, Herr Knippel! Ich freue mich, dass ich recht mit Ihnen hatte.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Wann werden wir anfangen, Kettenschuss meine Augen?";
			link.l1 = "Etwas später. Wir müssen uns darauf vorbereiten.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "22");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Du bist ein "+GetSexPhrase("Dieb, Herr! Wachen, nehmt ihn","Diebin, Mädchen! Wachen, nehmt sie")+"!!!","Nur schau dir das an! Kaum habe ich mich umgedreht, hast du beschlossen, meine Truhe zu durchsuchen! Greift den Dieb!!!","Wachen! Raub! Fangt den Dieb!!!");
			link.l1 = "Verdammt!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
