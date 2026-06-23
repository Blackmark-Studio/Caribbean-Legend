// диалог начальника шахты
void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	location = &Locations[FindLocation(pchar.location)];
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Du wagst es, dein Gesicht hier zu zeigen?! Weiß nicht, ob du mutig oder dumm bist...","Wie konnten diese Faulenzer einen Feind in meine Residenz eindringen lassen? Das ist mir unverständlich...","Meine Wachen sind tatsächlich keinen Kupfer wert, wenn solche Bastarde hier herumlaufen..."),LinkRandPhrase("Was brauchst du, "+GetSexPhrase("du Schurke","du Miststück")+"?! Meine Soldaten sind bereits auf deiner Spur "+GetSexPhrase(",dreckiger Pirat","")+"!","Dreckiger Mörder, verlasse sofort meine Residenz! Wachen!","Ich habe keine Angst vor dir, du "+GetSexPhrase("Ratte","Schlampe")+"! Bald wirst du in unserem Fort gehängt werden und danach wirst du nicht weit kommen..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Diese Soldaten sind keinen einzigen Peso wert...","Sie werden mich nie kriegen."),RandPhraseSimple("Halt dein Maul, "+GetWorkTypeOfMan(npchar,"")+", oder ich reiß dir die verdammte Zunge raus!","Ich würde dir vorschlagen, still zu sitzen, und vielleicht kommst du lebend davon..."));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(int(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = "Feind in der Mine! Alarm!";
				link.l1 = "Aaah, Teufel!";
				link.l1.go = "fight"; 
				break;
			}	
			dialog.text = LinkRandPhrase(""+TimeGreeting()+", Señor. Ich bin "+GetFullName(npchar)+", der Bergbauingenieur der Los-Teques-Mine. Was brauchst du hier?","Hallo, Señor. Was wollen Sie?","Hmm... wollten Sie etwas von mir, Señor? Ich höre zu.");
			if (!CheckAttribute(location, "quest.info"))
			{
				link.l9 = "Ich bin neu hier und möchte mehr über diese Mine erfahren...";
				link.l9.go = "info";
			}
			if (GetSquadronGoods(pchar, GOOD_SLAVES) > 4)
			{
				link.l2 = "Ich habe eine Ladung in meinem Laderaum, die dich interessieren könnte. Genau genommen Sklaven für deine Mine. Möchtest du handeln?";
				if (!CheckAttribute(location, "quest.slaves")) link.l2.go = "slaves_0";
				else link.l2.go = "slaves";
			}
			link.l1 = "Ich bin nur hereingekommen, um Hallo zu sagen, und ich gehe schon wieder.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = "Die Los-Teques-Mine fördert Gold für die spanische Krone. Alles, was wir fördern, gehört Spanien. Wir finden hier nicht nur Gold, sondern auch Silbernuggets und wertvolle Edelsteine. Wir verkaufen hier kein Gold, alles, was wir fördern, wird unter einem verstärkten Konvoi in die Alte Welt geliefert\nAber wir haben zwei Ausnahmen für goldene und silberne Nuggets. Erstens, Sie können eine bestimmte Menge von ihnen in unserem lokalen Laden von einem Quartiermeister kaufen. Manchmal kommt das Gehalt nicht rechtzeitig hier an, daher müssen wir hier einige Münzreserven für solche Fälle aufbewahren, deshalb ist der lokale Handel erlaubt\nZweitens, wir erleben ständig einen Bedarf an Arbeitskräften, daher tauschen wir Nuggets gegen Sklaven. Daher sprechen Sie mit mir, wenn Sie etwas anzubieten haben, wir werden Geschäfte machen\nIch glaube, dass die Regeln des Minenverhaltens offensichtlich sind: Nicht stehlen, Sträflinge nicht ablenken und Soldaten nicht belästigen, sonst werden Ihnen die Konsequenzen nicht gefallen.";
			link.l1 = "Gut, danke!";			
			link.l1.go = "exit";
			location.quest.info = "true";
		break;
		
		// генератор купли-продажи рабов
		case "slaves_0":
			location.quest.slaves.qty = 200; // стартовая потребность
			dialog.text = "Natürlich, Señor! Wie viele haben Sie?";
			link.l1 = "Ich habe "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
			link.l1.go = "slaves_1";
		break;
		
		case "slaves":
			location.quest.slaves.qty = int(location.quest.slaves.qty)+GetNpcQuestPastDayParam(location, "slave_date"); // каждый день даёт +1 потребности
			if (int(location.quest.slaves.qty) > 350) location.quest.slaves.qty = 350; // максимум потребности
			if (int(location.quest.slaves.qty) < 5)
			{
				dialog.text = "Señor, leider haben wir im Moment keinen Bedarf an mehr Sklaven. Aber die Situation kann sich jederzeit ändern, also schauen Sie in ein paar Wochen oder zu einem anderen Zeitpunkt wieder vorbei.";
				link.l1 = "In Ordnung, Señor, ich verstehe. Sie brauchen sie jetzt nicht, aber vielleicht brauchen Sie sie in einiger Zeit.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Natürlich, Señor! Wie viele haben Sie?";
				link.l1 = "Ich habe "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
				link.l1.go = "slaves_1";
			}
		break;
		
		case "slaves_1":
			dialog.text = "Für jeden Sklaven bin ich bereit, dir entweder einen Goldbarren oder zwei Silberbarren zu zahlen. Was wählst du?";
			link.l1 = "Goldbarren.";
			link.l1.go = "slaves_g";
			link.l2 = "Silberbarren.";
			link.l2.go = "slaves_s";
			link.l3 = "Es tut mir leid, Señor, aber ich habe meine Meinung gerade geändert. Ein andermal.";
			link.l3.go = "slaves_exit";
		break;
		
		case "slaves_g":
			location.quest.slaves.type = "gold";
			dialog.text = "Gut. Wie viele Sklaven wirst du mir verkaufen?";
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_s":
			location.quest.slaves.type = "silver";
			dialog.text = "Gut. Wie viele Sklaven wirst du mir verkaufen?";
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_trade":
			iTotalTemp = int(dialogEditStrings[6]);
			if (iTotalTemp < 1)
			{
				dialog.text = "Señor, ich habe keine Zeit für dumme Witze. Wenn du zum Scherzen aufgelegt bist, geh in die Taverne!";
				link.l1 = "Hmm...";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > GetSquadronGoods(pchar, GOOD_SLAVES))
			{
				dialog.text = "Señor, ich glaube, Sie müssen sich ausruhen. Vielleicht sind Sie sehr müde oder haben einen Hitzschlag bekommen. Gehen Sie in die Taverne, ruhen Sie sich gut aus, und dann können wir unsere Verhandlungen fortsetzen.";
				link.l1 = "Hmm...";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > int(location.quest.slaves.qty))
			{
				dialog.text = "Leider, Señor, benötigen wir im Moment nicht so viele Sklaven. Die Mine benötigt derzeit "+FindRussianQtyString(int(location.quest.slaves.qty))+". Wirst du so viele verkaufen?";
				link.l1 = "Ja, natürlich!";
				link.l1.go = "slaves_max";
				link.l2 = "Hmm... Ich denke, erst einmal nicht.";
				link.l2.go = "slaves_exit";
				break;
			}
			dialog.text = ""+FindRussianQtyString(iTotalTemp)+"? Ausgezeichnet. Bitte befehlen Sie, sie zum Stadttor zu bringen. Ich schicke meine Männer, um sie abzuholen.";
			link.l1 = "Machen Sie sich keine Sorgen, Señor. Ihre Sklaven werden Ihnen rechtzeitig geliefert. Ich werde sofort alle relevanten Befehle erteilen.";
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_max":
			iTotalTemp = int(location.quest.slaves.qty);
			dialog.text = "Ausgezeichnet. Bitte befehlen Sie, sie zum Stadttor zu bringen. Ich werde meine Männer für sie schicken.";
			link.l1 = "Machen Sie sich keine Sorgen, Señor. Ihre Sklaven werden Ihnen rechtzeitig geliefert. Ich werde sofort alle relevanten Befehle erteilen.";
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_calk":
			DialogExit();
			Log_Info("Der Austausch von Sklaven gegen Barren ist abgeschlossen");
			PlaySound("interface\important_item.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,5,10);
			RemoveCharacterGoods(pchar, GOOD_SLAVES, iTotalTemp);
			if (location.quest.slaves.type == "gold") TakeNItems(pchar, "jewelry5", iTotalTemp);
			else TakeNItems(pchar, "jewelry6", iTotalTemp*2);
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
			location.quest.slaves.qty = int(location.quest.slaves.qty)-iTotalTemp;
		break;
		
		case "slaves_exit":
			DialogExit();
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		    LAi_group_Attack(NPChar, Pchar);
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
