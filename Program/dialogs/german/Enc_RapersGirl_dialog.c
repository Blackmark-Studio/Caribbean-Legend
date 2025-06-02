void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iRnd, iRnd1;
	string sTemp, sGems;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit_1":
			AddDialogExitQuest("LandEnc_RapersTalk");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "exit":
			LAi_SetCitizenTypeNoGroup(NPChar);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "Begin_1":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Kapitän","Dame")+"! Bitte, sei gnädig! Beschütze mich, ich flehe dich an!","Hilfe! "+GetSexPhrase("Fremder","Junge Dame")+", rette mich, ich flehe dich an!");
			link.l1 = LinkRandPhrase("Was ist passiert?","Was ist los?",RandPhraseSimple("Was ist das Problem?","Was passiert?"));
			link.l1.go = "Begin_11";
		break;

		case "Begin_2":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Kapitän! Kapitän","Lass! Lass")+", bitte warte!","Halt an, "+GetSexPhrase("Kapitän","junge Dame")+"! Bitte.");
			link.l1 = LinkRandPhrase("Was ist passiert?","Was ist los?",RandPhraseSimple("Was ist das Problem?","Was passiert?"));
			link.l1.go = "Begin_21";
		break;

		case "Begin_3":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = "Oh, m"+GetSexPhrase("Schwester","fress")+"! Bitte, hilf einem armen Mädchen, ich flehe dich an! Diese Leute wollen mir etwas Schreckliches antun!";
			link.l1 = LinkRandPhrase("Was ist passiert?","Was ist los?",RandPhraseSimple("Was ist das Problem?","Was passiert?"));
			link.l1.go = "Begin_31";
		break;
		
		case "Begin_11":
			dialog.text = RandPhraseSimple("Diese Schurken wollen mich vergewaltigen! Um alles in der Welt, lass sie nicht!","Um Gottes willen, beschütze mich vor diesen Monstern! Sie werden mich entehren!");
			link.l1 = "Hör auf zu paniken"+GetSexPhrase(", Schönheit","")+". Was ist hier passiert?";
			link.l1.go = "exit_1";
		break;

		case "Begin_21":
			dialog.text = RandPhraseSimple("Vergewaltiger verfolgen mich!"+GetSexPhrase(" Würden Sie für die Ehre einer Dame eintreten?","")+"","Kapitän, "+GetSexPhrase("sei ein Mann","du bist auch eine Frau")+" würdest du nicht ein Mädchen vor Schande retten!");
			link.l1 = "Hör auf zu panikieren"+GetSexPhrase(", Schönheit","")+". Was ist hier passiert?";
			link.l1.go = "exit_1";
		break;
		
		case "Begin_31":
			dialog.text = "Sie verfolgen mich! Die Banditen! Sag ihnen, sie sollen mich in Ruhe lassen!";
			link.l1 = "Hör auf zu paniken"+GetSexPhrase(", Schönheit","")+". Was ist hier passiert?";
			link.l1.go = "exit_1";
		break;
		
		case "First time":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = LinkRandPhrase("Hilfe! Hilfe! Sie verfolgen mich! Rette mich!","Aaah! Hilfe, "+GetSexPhrase("Fremder","junge Dame")+"! Rette mich vor diesen Schurken!","Zeige Barmherzigkeit und schütze mich vor diesen Schurken! Bitte!");
			Link.l1 = LinkRandPhrase("Was passiert?","Wie geht's?","Was ist passiert?");
			Link.l1.go = "Node_2";			
		break;        

		case "Node_2":
			dialog.text = LinkRandPhrase("Sie... sie werden mich vergewaltigen! Um alles in der Welt, lass sie das nicht tun! Bitte!","Diese Bestien... sie planen etwas Schreckliches... Beschütze mich vor ihnen, bitte!","Im Namen unseres Herrn, rette mich vor diesen lüsternen Bestien! Sie wollen meine Ehre beschmutzen!");
			Link.l1 = "Lass uns alles klären, dann.";
			Link.l1.go = "exit_1";			
		break;

		case "ThanksForHelp":
			if(pchar.GenQuest.EncGirl == "Begin_11")
			{
				if(rand(1) == 0)
				{
					dialog.text = RandPhraseSimple("Danke, "+GetSexPhrase("Kapitän","junge Dame")+". Ich war so erschrocken!","Danke, dass Sie mich gerettet haben! Ich bin Ihnen so dankbar!");
					link.l1 = "In Ordnung, "+GetSexPhrase("Schönheit","Liebster")+", beruhige dich, es ist alles in der Vergangenheit.";
					link.l1.go = "Node_11";
				}
				else
				{
					dialog.text = "Oh, danke, "+GetSexPhrase("edler Mann! Sie sind ein echter Gentleman!","Frau! Sie haben mich gerettet!")+"";
					link.l1 = "Ich konnte nicht anders.";
					link.l1.go = "Node_12";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_22")
			{
				if(rand(1) == 0)
				{
					dialog.text = "Oh, danke, "+GetSexPhrase("edler Mann! Du bist ein echter Gentleman!","Fremder! Du hast mich gerettet!")+"";
					link.l1 = "Ich konnte nicht anders.";
					link.l1.go = "Node_12";	
				}
				else
				{
					dialog.text = "Was hast du getan? Warum hast du sie getötet?! Jetzt werden sie nach mir suchen! Mein Gott, was habe ich getan, um das zu verdienen!";
					link.l1 = "Jetzt ist das mal Dankbarkeit!";
					link.l1.go = "Node_22";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_33")
			{
				dialog.text = "Was hast du getan, "+GetSexPhrase("Kapitän","junge Dame")+"?! Warum hast du sie getötet? Sie wurden tatsächlich von meinem Vater geschickt... Oh Gott, jetzt wird er mich sicher töten...";
				link.l1 = "Das sind ja Neuigkeiten! Und was hast du dir dabei gedacht, zu schreien, dass du von Räubern verfolgt wurdest?!";
				link.l1.go = "Node_31";
			}
		break;
		
		case "Node_11":
			Diag.TempNode = "Node_1Next";
			addMoneyToCharacter(pchar, makeint((sti(pchar.rank))*25 + frand(2)*500));
			dialog.text = "Ich habe etwas Geld, bitte nimm es als Zeichen meiner Dankbarkeit. Ich werde jetzt jedem erzählen, "+GetSexPhrase("was für ein guter und edler Mann Sie sind","was für eine gute und noble Frau du bist")+".";
			link.l1 = "Sicher wirst du das. Danke... Jetzt geh einfach nach Hause.";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
		break;
		
		case "Node_12":
			dialog.text = "Ich kann mich immer noch nicht zusammenreißen. Könnten Sie bitte bringen "+GetSexPhrase("eine Dame","ich")+" zur Siedlung von "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+"? Weißt du, jetzt scheinen mir Vergewaltiger hinter jedem Busch zu lauern.";
			link.l1 = RandPhraseSimple("Mach dir nicht so viele Sorgen, wirklich... Gut, lass uns loslegen.","Du bist so ein Feigling, nicht wahr? Gut, ich bringe dich dorthin.");
			link.l1.go = "Node_121Next";
			link.l2 = "Es tut mir leid, Liebling, aber ich habe einfach keine Zeit, ich bin zu beschäftigt.";
			link.l2.go = "Node_3End";
		break;
						
		case "Node_22":
			dialog.text = "Ich dachte, du würdest sie nur abschrecken! Nun musst du mich zur Taverne in der Siedlung bringen "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+", Ich habe niemanden außer dir, den ich um Hilfe bitten könnte.";
			link.l1 = "Oh, verdammt! Also los. Bleib nur nicht zurück.";
			link.l1.go = "Node_122Next";
			link.l2 = "Nein, das ist es, "+GetSexPhrase("Schönheit","Lieber")+"! Ich habe für heute genug Überraschungen gehabt. Such dir jemand anderen, der dir hilft.";
			link.l2.go = "Node_3End";
		break;
		
		case "Node_31":
			dialog.text = "Und was musste ich tun?! Mein Vater will, dass ich den Sohn des Wucherers heirate, diesen Milchgesicht... nur weil sein Vater eine Menge Geld in seinen Kisten hat! Aber ich liebe einen anderen Mann! Bring mich bitte zu ihm...";
			link.l1 = "Was für eine Last du bist! Na gut, lass uns gehen. Ich kann dich jetzt nicht einfach hier lassen, oder?.. Wie heißt dein Auserwählter, wohin soll ich dich bringen?";
			link.l1.go = "Node_32";
			link.l2 = "Nein, das ist es, "+GetSexPhrase("Schönheit","Liebster")+"! Ich habe genug Überraschungen für heute. Such dir jemand anderen, der dir hilft.";
			link.l2.go = "Node_3End";
		break;
		
		case "Node_32":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = "Sein Name ist "+pchar.GenQuest.EncGirl.sLoverId+", er ist ein Neuling. Im Moment bleibt er in der Siedlung von "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+", versuchte dort einen Job zu finden, aber das sind harte Zeiten. Jeder spricht von einer Krise... Und jetzt gibt es für mich sowieso kein Zurück mehr.";
			link.l1 = "Eine Krise? Ha... Für einen echten Piraten ist eine Krise, wenn ein Handelskarawan am Horizont ist, aber kein Wind die Segel füllt...";
			link.l1.go = "Node_12Next";
		break;
		
		case "Node_12Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			Diag.CurrentNode = Diag.TempNode;
			pchar.GenQuest.EncGirl = "FindLover";
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_121Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_253";
			pchar.GenQuest.EncGirl = "FindCoins";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_122Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_12End":
			Diag.TempNode = "Node_12End";
			dialog.text = RandPhraseSimple("Weißt du, "+GetSexPhrase("Kapitän","junge Dame")+"? Ich hatte solche Angst, dass meine Beine immer noch ein wenig wackeln.","Oh, du weißt, ich war so erschrocken. Es ist großartig, dass Gott dich meinen Weg geschickt hat.");
			link.l1 = RandPhraseSimple("Gott sei Dank, du lebst noch.","Lass dir das nicht zu Herzen gehen. Es ist gut, dass es so ausgegangen ist, weißt du.");
			link.l1.go = "exit";
		break;
		
		case "Node_1Next":
			dialog.text = RandPhraseSimple("Danke, "+GetSexPhrase("Kapitän","junge Dame")+", noch einmal. Wirklich, ich bin dir so verpflichtet.","Vielen Dank, "+GetSexPhrase("Kapitän","junge Dame")+". Ich habe keine Ahnung, was ich ohne deine Hilfe tun würde.");
			link.l1 = RandPhraseSimple("Das sollte dir eine Lehre sein. Nun, viel Glück...","Nächstes Mal solltest du vorsichtiger sein... Jetzt, lauf nach Hause, ich habe Dinge zu erledigen.");
			link.l1.go = "Node_1End";
			link.l2 = "Wie konntest du nur so unvorsichtig sein? Warum bist du alleine in den Dschungel gegangen?";
			link.l2.go = "Node_13";
		break;
		
		case "Node_1End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_3End":
			Diag.TempNode = "Node_3Final";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "Node_3Final":
			Diag.TempNode = "Node_3Final";
			dialog.text = RandPhraseSimple("Haben Sie Ihre Meinung geändert?","Kapitän, es ist großartig, dass Sie Ihre Meinung geändert haben!");
			link.l1 = RandPhraseSimple("Nein-nein, Liebling, ich passe.","Hab keine falschen Hoffnungen...");
			link.l1.go = "exit";
		break;
		
		case "Node_13":
			if(pchar.GenQuest.EncGirl == "FindCoins") 
			{
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
				pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			}
			pchar.GenQuest.EncGirl = "Begin_11";
			switch(sti(pchar.GenQuest.EncGirl.variant))
			{
				case 0:
					if(rand(1) == 0)
					{
						dialog.text = "Sie werden wohl über mich lachen, aber... Ich habe einen Liebestrank gesammelt... Eine Hexe hat mir erzählt, dass es eine Wurzel gibt, die in Liebesangelegenheiten helfen kann.";
						link.l1 = "Oh mein Gott! Was "+GetSexPhrase("denken diese Frauen darüber nach","hast du daran gedacht")+"?! Anscheinend hast du eine Menge von ihnen gesammelt, es gab eine ganze Reihe von Bewerbern, die dich gejagt haben, ich hatte eine harte Zeit, sie alle abzuwehren. Ha-ha-ha-ha... Auf Wiedersehen.";
						link.l1.go = "Node_1End";
					}
					else
					{
						dialog.text = "Ich bin gerade ausgegangen, um ein paar Kräuter zu sammeln und frische Luft zu schnappen. Anscheinend war es nicht die beste Zeit für einen Spaziergang.";
						link.l1 = "Welche Nachlässigkeit?! Gott sei Dank bin ich rechtzeitig aufgetaucht. Nun, viel Glück Dir.";
						link.l1.go = "Node_1End";
					}
				break;
				case 1:
					dialog.text = "Meine Herrin hat irgendwo hier die Perlen ihrer Halskette verschüttet, als sie spazieren ging. Als sie nach Hause kam, schrie sie mich an und befahl mir, rauszugehen und sie zu sammeln. Sie sagte: 'Zeig mir dein Gesicht nicht einmal, bis du sie alle gesammelt hast!', Und ich kenne nicht einmal den genauen Ort. Außerdem, wie soll ich sie sowieso in diesem dicken Gras finden? Die Perlen sind so klein... Also, ich wandere hier nur ohne einen Hinweis darauf, was ich überhaupt tun soll...";
					link.l1 = "Und was für eine Halskette war das? Vielleicht wäre es einfacher, einfach eine neue zu kaufen, anstatt im Dschungel herumzuwandern? Wie viele Perlen hat deine Herrin verloren?";
					link.l1.go = "Node_131";
				break;
				case 2:
					dialog.text = "Mein verstorbener Vater hinterließ mir eine Karte, und seine Gefährten wollten sie mir abnehmen. Solange er lebte, zitterten sie alle vor ihm in Angst, aber gerade als ich ihn begraben hatte, begannen die schwierigen Zeiten. Zuerst versuchten sie, diese Karte von mir zu kaufen, aber ich weigerte mich, und so fingen sie an, mich einzuschüchtern.";
					link.l1 = "Und warum hast du es nicht einfach verkauft? Was ist so besonders an dieser Karte, dass Piratenbanden danach suchen?";
					link.l1.go = "Node_132";
				break;
			}	
		break;
		
		case "Node_131":
			pchar.GenQuest.EncGirl.SmallCoins = rand(25) + 20;
			pchar.GenQuest.EncGirl.BigCoins = rand(15) + 5;
			dialog.text = "Diese Halskette bestand aus ausgewählten Perlen, diese können nicht billig gekauft werden. Es gab "+sti(pchar.GenQuest.EncGirl.BigCoins)+" große Perlen und "+sti(pchar.GenQuest.EncGirl.SmallCoins)+" kleinere. Wenn diese Perlen gefunden würden, könnten wir eine weitere Halskette wie diese in Auftrag geben.";
			link.l1 = "Sicherlich wird das keine leichte Aufgabe... Nun, wenn deine Herrin dir einen Befehl gegeben hat, dann kannst du nicht viel tun. Versuche, die Perlen zu finden. Viel Glück.";
			link.l1.go = "Node_131End";
			link.l2 = "Es ist sinnlos. Es wäre einfacher, eine Nadel im Heuhaufen zu finden als die Perlen in diesem dicken Gras. Ganz zu schweigen davon, dass du nicht einmal den Ort kennst, an dem die Perlen verloren gingen...";
			link.l2.go = "Node_133";
		break;
		
		case "Node_131End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
			pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132":
			pchar.GenQuest.EncGirl.mapOwner = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1); 
			dialog.text = "Mein Vater hat einen Ort darauf markiert, an dem er seinen Schatz versteckt hat. Hast du von dem berühmten Piraten gehört "+GetName(NAMETYPE_ORIG,pchar.GenQuest.EncGirl.mapOwner,NAME_VOC)+"?";
			link.l1 = "Nein, habe noch nie von ihm gehört.";
			link.l1.go = "Node_132_1";
		break;
		
		case "Node_132_1":
			dialog.text = "Nun, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.EncGirl.mapOwner,NAME_NOM)+" war mein Vater. Jeder hatte Angst vor ihm, niemand würde es wagen, ein Wort zu äußern. Jetzt sind sie natürlich dreist geworden. Als ich mich weigerte, ihnen die Karte zu verkaufen, behaupteten sie, sie müssten auch ihren Anteil am Schatz haben. Ich wollte die Karte verstecken, aber sie haben mich trotzdem aufgespürt...";
			link.l1 = "Und warum würdest du es überhaupt verstecken? Chartern Sie ein Schiff und gehen Sie, fordern Sie Ihren Schatz. Dein Vater hätte es nicht umsonst versteckt.";
			link.l1.go = "Node_132_2";
		break;
		
		case "Node_132_2":
			dialog.text = "Leichter gesagt als getan. Ich habe kein Geld, um ein Schiff zu chartern, und... Ich habe Angst... Wie soll ich das alles ausgraben, es zum Schiff tragen... Und wo sollte ich den Schatz danach hinbringen? Jeder würde mich unterwegs zur leichten Beute machen...";
			link.l1 = "Das ist ein guter Punkt... Also gut, verstecke deine Karte. Denk nur daran, sie gut zu platzieren.";
			link.l1.go = "Node_132_2End";
			if(GetCharacterItem(pchar, "map_full") == 0)
			{
				link.l2 = "Hmm... Das ist wahrscheinlich wahr. Umso mehr hättest du es verkaufen sollen.";
				link.l2.go = "Node_132_3";
			}
			link.l3 = "Haben Sie versucht, einen Gefährten zu finden?";
			link.l3.go = "Node_132_8";	
		break;
		
		case "Node_132_2End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_3":
			dialog.text = "Es schmerzt mich, eine solche Gelegenheit zu verpassen... Vater erzählte mir von den Schätzen, die er dort versteckt hat. Niemand würde mir so viel bezahlen...";
			link.l1 = "Nun, verkaufe es nicht zu billig. Und überhaupt, Gold ist dein Leben nicht wert. Ganz zu schweigen davon, dass dies der einfachste Weg für dich ist, du sammelst einfach dein Geld und befreist dich von allen Problemen...";
			link.l1.go = "Node_132_4";
		break;
		
		case "Node_132_4":
			pchar.GenQuest.EncGirl.mapPrice = 20000 + 500 * sti(pchar.rank);
			dialog.text = "Das klingt verlockend... Und wie viel kannst du mir dafür bieten?";
			link.l1 = "Ich glaube nicht, dass es mehr wert sein kann als "+sti(pchar.GenQuest.EncGirl.mapPrice)+" Pesos.";
			link.l1.go = "Node_132_5";
		break;
		
		case "Node_132_5":
			if((GetSummonSkillFromName(pchar, SKILL_COMMERCE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)) > (rand(220) + 100) && (makeint(pchar.money) >= sti(pchar.GenQuest.EncGirl.mapPrice)))
			{
				dialog.text = "Heh, eine Frau zu sein ist nicht einfach... Gut, ich stimme zu. Endlich wird dieser Alptraum vorbei sein... Vielleicht ist es am besten, diese Karte gehört dir,"+GetSexPhrase(" ein edler Herr","")+", als zu diesen Halunken.";
				link.l1 = "Gut. Hier ist dein Geld... versuche einfach, es nicht auf einmal auszugeben.";
				link.l1.go = "Node_132_6";
			}
			else
			{
				dialog.text = "Nein, "+GetSexPhrase("Kapitän","junge Dame")+". Ich werde es nicht verkaufen. Ich werde einen guten Mann heiraten, und dann werden wir gemeinsam den Schatz beanspruchen.";
				link.l1 = "Nun, das liegt bei dir zu entscheiden. Dein Stück Papier ist sowieso nicht mehr wert.";
				link.l1.go = "Node_132_2End";
			}	
		break;
		
		case "Node_132_6":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.mapPrice))); 
			ref rMap = ItemsFromID("map_full"); // mitrokosta фикс пустой карты
			FillMapForTreasure(rMap);
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_8":
			dialog.text = "Und wo finde ich sie? Die jungen sind nicht zuverläßig und sie kümmern sich nicht so sehr um Schätze wie um andere Dinge. Und ich fürchte die älteren, sie erinnern mich alle an die Kumpels meines Vaters. So gerissen und verräterisch, man weiß nie, was man von ihnen erwarten kann.";
			link.l1 = "Ha-ha-ha... Also gut, aber nimmst du mich mit dir?";
			link.l1.go = "Node_132_9";
		break;
		
		case "Node_132_9":
			dialog.text = "Du? Und würdest du gehen? Aber dann musst du mich hierher zurückbringen, zur Siedlung von "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+", in Ordnung?";
			link.l1 = "Gut, ich gebe dir mein Wort. Zeig mir nur den Weg.";
			link.l1.go = "Node_132_10";
		break;
		
		case "Node_132_10":
			EncGirl_GenQuest_GetChestPlaceName();
			dialog.text = "Der Schatz ist in der Höhle auf "+XI_ConvertString(pchar.GenQuest.EncGirl.islandId+"Konto")+", wir müssen an Land gehen bei "+XI_ConvertString(pchar.GenQuest.EncGirl.shoreId+"Gen")+", der Ort, wo ich mich zeigen werde... Aber vergiss nicht, du bekommst nur die Hälfte!";
			link.l1 = "In Ordnung, ich werde dich nicht betrügen, das verspreche ich. Folge mir und bleib nicht zurück.";
			link.l1.go = "Node_132_11";
		break;
		
		case "Node_132_11":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "4");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sTreasureLoc", XI_ConvertString(pchar.GenQuest.EncGirl.islandId));
			AddQuestUserData("JungleGirl", "sShore", XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen"));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			pchar.quest.EncGirl_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_Death.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_Death.function = "EncGirl_Death";
			pchar.quest.EncGirl_FindChest.win_condition.l1 = "location";
			pchar.quest.EncGirl_FindChest.win_condition.l1.location = pchar.GenQuest.EncGirl.placeId;
			pchar.quest.EncGirl_FindChest.function = "EncGirl_FindChest";
			SetFunctionExitFromLocationCondition("EncGirl_AddPassenger", pchar.location, false);
			SetFunctionLocationCondition("EncGirl_DialogAtShore", pchar.GenQuest.EncGirl.shoreId, false);
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "GetChest";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_11_1":
			dialog.text = "Kapitän, jetzt müssen wir die Höhle finden.";
			link.l1 = "Gut, schauen wir uns das jetzt an.";
			link.l1.go = "exit";
			Diag.TempNode = "Node_132_11_2";
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
		break;
		
		case "Node_132_11_2":
			Diag.TempNode = "Node_132_11_2";
			dialog.text = "Kapitän, wir müssen die Höhle finden.";
			link.l1 = "In Ordnung, lass uns jetzt mal schauen.";
			link.l1.go = "exit";
		break;
		
		case "Node_132_12":
			dialog.text = "Hier! Ich habe es gefunden! Genau wie mein Vater es gesagt hat! Ein riesiger Schatzhaufen! Die Hälfte gehört dir, wie abgemacht.";
			link.l1 = "Siehst du? Das war nicht schwer, also gab es nichts zu fürchten.";
			link.l1.go = "Node_132_13";
		break;
		
		case "Node_132_13":
			dialog.text = "Ha-ha-ha! Ich bin jetzt reich! Nimmst du jetzt deinen Anteil?";
			link.l1 = "Ich vermute.";
			link.l1.go = "Node_132_15";
		break;
		
		case "Node_132_15":
			dialog.text = "Dann nimm es und hilf mir bitte, all das Zeug zum Schiff zu tragen. Erinnerst du dich noch daran, dass du versprochen hast, mich nach Hause zu bringen?";
			link.l1 = "Ich habe es nicht vergessen! Sicher, ich nehme dich mit.";
			link.l1.go = "Node_132_16";
		break;
		
		case "Node_132_16":
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			PChar.quest.EncGirl_DialogAtShore.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.		
			LAi_LocationDisableMonstersGen(pchar.location, false);
			chrDisableReloadToLocation = false;
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+hrand(1));
			TakeNItems(pchar, "chest", 2+hrand(6));
			TakeNItems(pchar, "jewelry1", 30+hrand(15));
			TakeNItems(pchar, "jewelry2", 30+hrand(15));
			TakeNItems(pchar, "jewelry3", 30+hrand(15));
			TakeNItems(pchar, "jewelry4", 30+hrand(15));
			TakeNItems(pchar, "jewelry5", 30+rand(10));
			TakeNItems(pchar, "jewelry6", 10+rand(10));
			TakeNItems(pchar, "jewelry42", 20+rand(10));
			TakeNItems(pchar, "jewelry44", 30+rand(10));
			TakeNItems(pchar, "jewelry46", 50+rand(20));
			AddQuestRecord("JungleGirl", "6");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));		
			pchar.GenQuest.EncGirl = "ChestGetted";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_DeathAgain.function = "EncGirl_DeathAgain";
			Diag.TempNode = "Node_132_17";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			pchar.quest.EncGirl_AddPassenger.win_condition.l1 = "location";// лесник на корабль девицу. 
			pchar.quest.EncGirl_AddPassenger.win_condition.l1.location = pchar.location.from_sea;
			pchar.quest.EncGirl_AddPassenger.function = "EncGirl_AddPassenger";
		break;
		
		case "Node_132_17":
			Diag.TempNode = "Node_132_17";
			dialog.text = "Reich zu sein ist einfach großartig! Ich fühle mich jetzt so anders."; 
			link.l1 = "Ich freue mich für dich.";
			link.l1.go = "exit";
		break;
		
		case "Node_132_18":
			dialog.text = "In Ordnung, Kapitän. Meine Reise ist jetzt vorbei. Danke für Ihre Hilfe.";
			link.l1 = "Bitte sehr... Also, was planen Sie mit Ihrem neugewonnenen Reichtum zu tun? Kaufen Sie eine Plantage mit Sklaven?";
			link.l1.go = "Node_132_19";
		break;
		
		case "Node_132_19":
			dialog.text = "Ich weiß noch nicht, ich habe mich noch nicht entschieden. Vielleicht ziehe ich nach Europa...";
			link.l1 = "Also gut, nun! Viel Glück für dich.";
			link.l1.go = "Node_132_20";
		break;
		
		case "Node_132_20":
			dialog.text = "Halte an... Dieser Trödel war unter den Schätzen meines Vaters. Ich habe keine Verwendung dafür, aber es könnte dir gefallen. Bitte, nimm es als meine persönliche Dankbarkeit für das, was du für mich getan hast. Das ist von meinem Anteil, ha-ha-ha!";
			link.l1 = "Wow, das ist wirklich ein schönes Geschenk. Danke"+GetSexPhrase(", Schönheit","")+". Finde einen netten Bräutigam für dich, willst du...";
			link.l1.go = "Node_132_21";
		break;
		
		case "Node_132_21":
			chrDisableReloadToLocation = false;		
			RemovePassenger(pchar, npchar);			
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			AddQuestRecord("JungleGirl", "8");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
            LAi_SetActorType(npchar); // отправил восвояси чтоб не стояла. лесник.
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
            pchar.quest.EncGirl_EnterToSea.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.	
            PChar.quest.EncGirl_DialogAtShore.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.						
		break;
		
		case "Node_133":
			dialog.text = "Aber was kann ich tun? Ich kann die Befehle meiner Herrin nicht ignorieren, sie wird mich bei lebendigem Leib häuten.";
			link.l1 = "Warte auf mich in der Kirche der Siedlung "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+", Ich bringe dir die Perlen, um eine neue Halskette zu machen.";
			link.l1.go = "Node_133_1";
			if(sti(pchar.money) >= 15000)
			{
				link.l2 = "Hier. Nimm diese 15000 Pesos. Das sollte mehr als genug sein, um die Perlen für die Halskette auszuwählen, oder um eine neue zu kaufen.";
				link.l2.go = "Node_135";
			}							
		break;
		
		case "Node_133_1":
			pchar.GenQuest.EncGirl = "GetCoins";
			pchar.quest.EncGirl_Coins.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_Coins.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_Coins.function = "EncGirl_toChurch";
			pchar.quest.EncGirl_GetCoins.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.function = "EncGirl_GenQuest_GetCoins";	
            sTemp = LAi_FindNearestFreeLocator2Pchar("reload");// лесник - девица убегает если ГГ сказал ждать в цервки
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);			
			Diag.TempNode = "Node_134"; 
			Diag.CurrentNode = Diag.TempNode;
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "1"); 
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","")); 
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sText1", sti(pchar.GenQuest.EncGirl.BigCoins)); 
			AddQuestUserData("JungleGirl", "sText2", sti(pchar.GenQuest.EncGirl.SmallCoins)); 		
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_134":
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Kapitän","Junge Dame")+", Ich bin so froh, dich wieder zu sehen! Hast du es geschafft, Perlen für die Halskette zu sammeln?","Hallo, Kapitän! Haben Sie mir die Perlen gebracht? Sie wissen, meine Herrin wird so nervös...");
			if (GetCharacterItem(pchar, "jewelry52") >= sti(pchar.GenQuest.EncGirl.BigCoins) && GetCharacterItem(pchar, "jewelry53") >= sti(pchar.GenQuest.EncGirl.SmallCoins))
			{
				link.l1 = "Ja. Hier sind deine Perlen. Bring sie zu deiner Herrin und sag ihr, sie soll nächstes Mal vorsichtiger sein.";
				link.l1.go = "Node_134_1";
			}
			else
			{
				link.l1 = "Noch nicht. Es ist nicht so einfach, weißt du... Aber ich bringe sie, warte nur ab.";
				link.l1.go = "Node_134_2";
			}	
		break;
		
		case "Node_134_1":
			TakeNItems(pchar, "jewelry52", -sti(pchar.GenQuest.EncGirl.BigCoins)); 
			TakeNItems(pchar, "jewelry53", -sti(pchar.GenQuest.EncGirl.SmallCoins)); 
			pchar.quest.EncGirl_GetCoins.over = "yes";
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			dialog.text = "Oh, "+GetSexPhrase("Kapitän","junge Dame")+", Ich bin so glücklich, dass ich dich getroffen habe! Als Zeichen meiner Dankbarkeit für alles, was du für mich getan hast, möchte ich dir diesen Anhänger und diese Edelsteine geben. Ich hoffe wirklich, dass du sie nützlich finden würdest.";
			link.l1 = "Wow! Nun, danke auch dir"+GetSexPhrase(", Schönheit","")+", Ich habe nicht erwartet... Auf Wiedersehen, und sei glücklich.";
			link.l1.go = "Node_134_End";
		break;
		
		case "Node_134_2":
			dialog.text = "Oh, "+GetSexPhrase("Kapitän","junge Dame")+", ich zähle auf dich.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_SetStayType(NPChar);
		break;
		
		case "Node_134_End":
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			TakeNItems(pchar, "jewelry1", 15+hrand(8));
			AddQuestRecord("JungleGirl", "2");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_135":
			addMoneyToCharacter(pchar, -15000);
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			dialog.text = "Oh, "+GetSexPhrase("Kapitän","junge Dame")+", du hast mir heute zum zweiten Mal geholfen. Vielen Dank. Ich werde deine Freundlichkeit nie vergessen.";
			link.l1 = "Bitte sehr. Sag 'Hallo' zu deiner Herrin...";
			link.l1.go = "Node_135End";
		break;
		
		case "Node_135End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			NPChar.lifeDay = 0;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;	
		
		case "ThanksForSave":
			if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga") 
			{
				if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse")) 
				{
					iRnd = 2;
					pchar.GenQuest.EncGirl.BrothelCity = true;
				}	
				else
				{	
					iRnd = 1;
				}	
			}
			else
			{
				iRnd = 1;
			}
			switch(rand(iRnd))
			{
				case 0:
					dialog.text = RandPhraseSimple("Du hättest ihnen kein Geld geben sollen. Sie haben gelogen.","Glaub ihnen nicht. Sie sind Lügner. Und du hättest ihnen kein Geld geben sollen.");
					link.l1 = "Hätte ich sie töten sollen?";
					link.l1.go = "Node_200";
				break;
				case 1:
					dialog.text = "Oh, was für eine edle Tat! Ich konnte sofort sehen, dass du "+GetSexPhrase("ein echter Gentleman","eine edle Dame")+"! Bitte, akzeptieren Sie meine aufrichtigste Dankbarkeit. Ich hoffe, Sie haben nicht geglaubt, was diese Schurken gesagt haben?";
					link.l1 = "Das spielt keine Rolle. Ein Mädchen und eine Bande von Taugenichtsen im Dschungel, es ist einfach so natürlich...";
					link.l1.go = "Node_210";
					link.l2 = "Wovon redest du, "+GetSexPhrase("Schönheit","Liebster")+"? Wie könnte ich?";
					link.l2.go = "Node_211";
				break;
				case 2:
					dialog.text = "Danke, Kapitän. Es tut mir leid, dass ich Sie in diese unangenehme Angelegenheit verwickelt habe, aber ich hatte einfach keine andere Wahl.";
					link.l1 = "Nun, ich sehe, dass du auch ziemlich feststeckst. Wie ist es dazu gekommen?";
					link.l1.go = "Node_220";		
				break;
			}
		break;
		
		case "Node_200":
			if(rand(1) == 0)
			{
				dialog.text = "Vielleicht... Sie werden mich jetzt nie in Ruhe lassen.";
				link.l1 = "Ach komm schon! Geh einfach nach Hause, du hast jetzt nichts mehr zu fürchten.";
				link.l1.go = "Node_200End";
				link.l2 = "Wow! Warum hast du so eine Abneigung gegen Männer?";
				link.l2.go = "Node_201";
			}
			else
			{
				dialog.text = "Natürlich nicht! Aber sie lassen mich trotzdem nicht in Ruhe. Würden Sie mich zur Siedlung bringen "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+", bitte?";
				link.l1 = "Geh einfach nach Hause, sie werden dich nicht berühren. Sie sollten jetzt gerade zur Taverne gehen, um ihr leicht verdientes Geld zu verschwenden.";
				link.l1.go = "Node_200End";
				link.l2 = RandPhraseSimple("Mach dir nicht so viele Sorgen, wirklich... Gut, lass uns loslegen.","Du bist so ein Feigling, nicht wahr? Gut, ich bringe dich dort hin..");
				link.l2.go = "Node_121Next";
			}
		break;
		
		case "Node_201":
			dialog.text = "Oh nein, was sagst du da? Ich kenne diese Halunken nur zu gut. Sie waren ehemalige Kameraden meines Vaters. Sie versuchen, den Ort zu finden, an dem er seine Schätze versteckt hat.";
			link.l1 = "Und was ist mit deinem Vater los?";
			link.l1.go = "Node_202";
		break;
		
		case "Node_202":
			dialog.text = "Er war einmal Kapitän eines Piratenschiffes. Kürzlich starb er... Sie waren alle so höflich während der Beerdigung, aber mit der Zeit haben sie ihn vergessen, und kurz danach auch ihre Ehre und Ehrlichkeit. Es ist gut, dass ich sie bemerkt habe. Sobald sie erfahren, wo die Schätze sind, bin ich erledigt.";
			link.l1 = "Das ist eine traurige Geschichte. Also, planst du weiterhin, dich vor ihnen zu verstecken?";
			link.l1.go = "Node_203";
		break;
		
		case "Node_203":
			dialog.text = "Ich kann keine Juwelen zu Hause aufbewahren, ich habe niemanden, der mich beschützt. Also gehe ich nachts in die Höhle, wenn das Geld ausgeht...\nBring mich bitte zur Höhle, und ich gebe dir das Geld, das du ihnen gegeben hast ... Ich denke, die Piraten würden es nicht wagen, uns zu folgen, während du bei mir bist.";
			link.l1 = "Entschuldigung, Liebling, aber ich habe andere Pläne. Du wirst deinen Schatz ein anderes Mal sammeln.";
			link.l1.go = "Node_200End";
			link.l2 = "Gut, lass uns gehen, wenn du keine Angst vor mir hast.";
			link.l2.go = "Node_204";
		break;
		
		case "Node_204":
			dialog.text = "Sie wissen, aus irgendeinem Grund bin ich nicht...";
			link.l1 = "Nun, das ist eine gute Sache.";
			link.l1.go = "Node_205";
		break;
		
		case "Node_205":
			Diag.TempNode = "Node_206";
			EncGirl_GenerateChest(npchar);
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_206":
			Diag.TempNode = "Node_206";
			dialog.text = "Kapitän, du hast versprochen, mich zur Höhle zu bringen.";
			link.l1 = "Lass uns gehen...";
			link.l1.go = "exit";
		break;
		
		case "Node_207":
			dialog.text = "In Ordnung, Kapitän, ich habe so viel genommen, wie ich brauchte. Wir können jetzt zurückkehren.";
			link.l1 = "Deine Kumpels sind nicht in der Nähe, sehe ich.";
			link.l1.go = "Node_208";
		break;
		
		case "Node_208":
			dialog.text = "Gott sei Dank. Ich brauche nicht noch mehr Ärger... Hier, nimm diese Barren... das sollte genug sein, um deine Ausgaben zu decken. Geh alleine, ich nehme einen anderen Weg...";
			link.l1 = "Also gut, viel Glück für dich, wenn du keine Angst hast.";
			link.l1.go = "Node_209";
		break;
		
		case "Node_209":
			LAi_LocationDisableMonstersGen(pchar.location, false);
			i = makeint(sti(pchar.GenQuest.EncGirl.price)/100.0);
			TakeNItems(pchar, "jewelry6", i);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			pchar.quest.EncGirl_RapersExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_RapersExit.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_RapersExit.function = "EncGirl_MeetRapers";
			DialogExit();
		break;
		
		case "Node_200End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_210":
			dialog.text = "Hmm, "+GetSexPhrase("Kapitän","junge Dame")+", Ich mag deine Ironie nicht.";
			link.l1 = "Du kannst gehen, "+GetSexPhrase("Schönheit","Liebster")+". Und Sie sollten sich lieber beeilen, in die Stadt zu kommen, bevor sie Sie wieder jagen.";
			link.l1.go = "Node_1End";
		break;
		
		case "Node_211":
			dialog.text = "Ich war so aufgeregt! Könnten Sie mich bitte zur Taverne in der Siedlung bringen "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+"? Ansonsten fürchte ich, sie werden mich wieder jagen.";
			link.l1 = "Vielleicht hast du recht. Lass uns gehen...";
			link.l1.go = "Node_122Next";
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
		break;
		
		case "Node_220":
			dialog.text = "Oh, Kapitän, das ist eine lange Geschichte, und ich bin nicht sicher, ob Sie es interessant finden würden. Obwohl... Ich werde es jetzt trotzdem nicht ohne Ihre Hilfe tun. Könnten Sie mich bitte zur Taverne in der Siedlung bringen "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+"? Ich fürchte, sie würden mich einfach nicht in Ruhe lassen.";
			link.l1 = "Entschuldigung, Liebling, ich habe keine Zeit dafür. Ich habe Dinge zu erledigen.";
			link.l1.go = "Node_221";
			link.l2 = "Warum bist du so geheimnisvoll?";
			link.l2.go = "Node_222";
		break;
		
		case "Node_221":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_222":
			dialog.text = "Und wie kann ich nicht geheimnisvoll sein, wenn jeder versucht, aus meinem Unglück Profit zu schlagen?";
			link.l1 = "In Ordnung, dann...";
			link.l1.go = "Node_223";
		break;
		
		case "Node_223":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();		
		break;
		
		case "Node_224":
			dialog.text = "Kapitän, Sie haben versprochen, mich zur Taverne in der Siedlung zu bringen "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+".";
			link.l1 = RandPhraseSimple("Ich erinnere mich.","Mach dir keine Sorgen, ich werde dich dort sehen.");
			link.l1.go = "exit";
		break;
		
		case "Node_225":
			chrDisableReloadToLocation = false;
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (CheckAttribute(pchar, "GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15)
				{
					dialog.text = "Da sind zu viele Leute. Lass uns in den privaten Raum gehen. Ich muss dir etwas erzählen.";
					link.l1 = LinkRandPhrase("Ich habe schon zu viel für dich getan, also lebe wohl jetzt.","Du solltest meinen Gefallen nicht missbrauchen. Auf Wiedersehen, Liebling.","Ich habe keine Notwendigkeit für deine Geschichten von jetzt an, du kannst alles selbst herausfinden.");
					link.l1.go = "Node_226";
					link.l2 = "Hmm, gut. Dann nehme ich die Schlüssel vom Barkeeper.";
					link.l2.go = "Node_227";
				}
				else
				{
					dialog.text = "Vielen Dank für Ihre Hilfe, Kapitän. Ich werde es nicht vergessen.";
					link.l1 = "Oh, mach dir keine Mühe. Versuch einfach, in Zukunft vorsichtiger zu sein.";
					link.l1.go = "Node_226_1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin") // Addon-2016 Jason, французские миниквесты (ФМК)
				{
					dialog.text = "Vielen Dank für Ihre Hilfe, Kapitän. Ich werde es nicht vergessen.";
					link.l1 = "Oh, mach dir keine Sorgen. Sei einfach in der Zukunft vorsichtiger.";
					link.l1.go = "Node_226_1";
				}
				else
				{
					dialog.text = "Da sind zu viele Leute. Lass uns in den Privatraum gehen. Ich muss dir etwas sagen.";
					link.l1 = LinkRandPhrase("Ich habe schon zu viel für dich getan, also leb wohl jetzt.","Du solltest meine Gunst nicht missbrauchen. Auf Wiedersehen, Liebling.","Ich habe keine Notwendigkeit für deine Geschichten von nun an, du kannst alles selbst herausfinden.");
					link.l1.go = "Node_226";
					link.l2 = "Hmm, in Ordnung. Dann nehme ich die Schlüssel vom Barkeeper.";
					link.l2.go = "Node_227";
				}
			}
		break;
		
		case "Node_226":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_226_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_227":
			pchar.GenQuest.EncGirl = "EncGirl_ToTavern";
			pchar.quest.EncGirl_inRoom.win_condition.l1 = "location";
			pchar.quest.EncGirl_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			pchar.quest.EncGirl_inRoom.function = "EncGirl_SpeakInRoom";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_228":
			if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse") && CheckAttribute(pchar,"GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15) // душещипательная история о невинной девочке попавшей в бордель
			{
				DeleteAttribute(pchar, "GenQuest.EncGirl.BrothelCity");
				dialog.text = "Also, möchtest du immer noch meine Geschichte hören?";
				link.l1 = "Hmm... Ich denke, es ist Zeit für mich zu gehen. Tschüss!";
				link.l1.go = "Node_232";
				link.l2 = "Nun, spuck es aus, dann.";
				link.l2.go = "Node_233";	
			}
			else						
			{
				dialog.text = "Oh, mein edler Retter, endlich kann ich dir auf die Weise danken, wie nur eine Frau danken kann\nAls ich dich im Dschungel sah, hat sich alles in mir verändert. Ich vergaß die Vergewaltiger und die scharfen Palmenblätter, die meine Wangen peitschten. Vergaß, wohin zu laufen, warum zu laufen ... Ich sah nur dich. Und wollte nur dich ... Und nach dem, was du für mich getan hast...";
				link.l1 = "Wow! Was für ein Temperament! Eure Verfolger wussten sicher, wen sie jagen sollten...";
				link.l1.go = "Node_229"; // ГГ допрыгался - щас его попросту трахнут
				link.l2 = "Hör zu, Schönheit, ich kann es perfekt verstehen, aber bitte, behalte deine Laune für dich.";
				link.l2.go = "Node_230"; // Послал в пешее эротическое путешествие
			}
		break;
		
		case "Node_229":
			dialog.text = "Komm jetzt zu mir, mein Held...";
			link.l1 = "Oh, Liebling...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "EncGirl_facking";
			DoQuestCheckDelay("PlaySex_1", 3.0);
		break;
		
		case "Node_230":
			dialog.text = "Oh! Wie... Wie kannst du es wagen?! Was für ein Bastard! Ein Mädchen hat dir aus tiefstem Herzen gedankt, und du...";
			link.l1 = "Nun, wenn du nicht so viel geflirtet und dich nicht auf den ersten Mann gestürzt hättest, den du getroffen hast, hättest du sicherlich weniger Ärger gehabt. Ich rette solche Flirts nicht mehr im Dschungel...";
			link.l1.go = "Node_231";
		break;
		
		case "Node_231":
			dialog.text = "Ich habe noch nie solche Worte von jemandem gehört! Und ich werde sie nicht vergeben! Du wirst dich noch an mich erinnern!";
			link.l1 = "Geh schon, in Ordnung? Und versuche, dich aufzufrischen, es sei denn, du willst wieder gerettet werden...";
			link.l1.go = "Node_231_1";
		break;
		
		case "Node_231_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","", -1.0);
			npchar.lifeDay = 0;
			DoQuestFunctionDelay("EncGirl_SetBerglar", 5.0);
			DialogExit();		
		break;
		
		case "Node_232":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_233":
			pchar.GenQuest.EncGirl.Parents_City = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			dialog.text = "Meine Familie lebt in der Siedlung von "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.Parents_City)+". Ich kam zufällig hierher, auf dem Schiff, auf dem mein Bräutigam mich zu seinen Eltern brachte, aber es wurde von Piraten gefangen genommen. Das Schiff wurde weggenommen, und die Passagiere wurden in einer Bucht nicht weit von hier gelandet. Mein Bräutigam wurde während des Enterns des Schiffes getötet, und ich war während des Übergangs durch den Dschungel ernsthaft krank. \nDie Dame des örtlichen Bordells hat mich behandelt, und als ich auf die Beine kam, verlangte sie, dass ich das für die Behandlung ausgegebene Geld arbeite. Ich war eine Hure, aber ich erfreute die Madame nicht, und so verkaufte die Dame mich an einige Banditen, um zumindest etwas Geld zu verdienen. Den anderen Teil der Geschichte kennst du.";
			link.l1 = "So hör doch auf und kehr nach Hause zurück! Warum lässt du zu, dass sie dich wie einen Sklaven behandeln?!";
			link.l1.go = "Node_234";
		break;
		
		case "Node_234":
			dialog.text = "Ich kann nicht! All meine Sachen: anständige Kleidung, Geld, Dokumente... Sie sind alle in dem Bordell in meiner Reisetasche. Ich habe sie im Dating-Raum versteckt. Und während ich so gekleidet bin, werden alle Seeleute im Hafen hinter mir herlaufen. Und wer wird mich ohne Dokumente oder Geld an Bord nehmen? Und jetzt kann ich nicht einmal mehr mein Gesicht in der Stadt zeigen, oder ich werde hinter Gitter geworfen...";
			link.l1 = "Sollte kein Problem sein. Los geht's. Ich bringe dich persönlich nach Hause.";
			link.l1.go = "Node_235";
			link.l2 = "Warte hier. Ich bringe dir deine Reisetasche.";
			link.l2.go = "Node_236";													
			if(sti(pchar.money) >= 5000) 
			{
				link.l3 = "Wen kümmern Ihre Papiere? Wie viel Geld brauchen Sie, um nach Hause zu kommen?";
				link.l3.go = "Node_237";							
			}			
		break;
		
		case "Node_235":
			dialog.text = "Oh, danke dir, Kapitän... Aber... du weißt, ich habe nichts, um dich zu bezahlen.";
			link.l1 = "Wovon für eine Bezahlung redest du? Lass uns gehen, bevor sie gefunden werden...";
			link.l1.go = "Node_240";				
		break;
		
		case "Node_240":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "20");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			AddQuestUserData("JungleGirl", "sBrothelCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city + "Gen"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			OfficersReaction("bad");
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 3.0);
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1.location = pchar.GenQuest.EncGirl.Parents_City + "_town";
			pchar.quest.EncGirl_DeliveToParents.function = "EncGirl_DeliveToParents";
			DialogExit(); 		
		break;
		
		case "Node_236":
			dialog.text = "Oh, Kapitän, Sie wissen, ich würde niemals wagen zu fragen...";
			link.l1 = "Hab keine Angst. Bald werde ich zurück sein.";
			link.l1.go = "Node_239";				
		break;		
		
		case "Node_239":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "21");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);

			pchar.quest.EncGirl_GenerateBag.win_condition.l1 = "location";
			if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > rand(100))
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoomUp";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_Brothel_room";
			}
			else
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoom";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_SecBrRoom";
			}
			pchar.quest.EncGirl_GenerateBag.function = "EncGirl_GenerateLeatherBag";

			pchar.quest.EncGirl_GetBagFail.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.function = "EncGirl_GenQuest_GetBag";
						
			pchar.quest.EncGirl_ExitRoom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitRoom.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitRoom.function = "EncGirl_ExitTavernRoom";

			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
		
		case "Node_240_1":
			pchar.quest.EncGirl_GetBagFail.over = "yes";
			dialog.text = "Oh, ich habe mir schon Sorgen gemacht, dass dir etwas passiert sein könnte.";
			if(CheckCharacterItem(pchar, "leather_bag"))
			{
				link.l1 = "Was könnte schon passieren? Hier, nimm deine Sachen.";
				link.l1.go = "Node_241";
			}	
			else
			{
				link.l1 = "Hör zu, ich habe dort nichts gefunden. Bist du sicher, dass du deine Reisetasche im Verabredungsraum gelassen hast?";
				link.l1.go = "Node_242";			
			}	
		break;
		
		case "Node_241":
			TakeNItems(pchar, "leather_bag", -1);
			dialog.text = "Danke, "+GetSexPhrase("edler Kapitän","edles Mädchen")+". Ich werde nie vergessen, was du für mich getan hast. Ich habe nicht viel, aber bitte nimm dieses Amulett an. Vielleicht war es dieses Kleinod, das mein Leben während des Piratenangriffs gerettet hat.";
			link.l1 = "Danke und gute Reise! Leb wohl jetzt...";
			link.l1.go = "Node_243";
		break;
		
		case "Node_242":
			dialog.text = "Haben sie wirklich meine Tasche gefunden?";
			if(sti(pchar.money) >= 5000)
			{
				link.l1 = "Wie viel Geld brauchst du, um nach Hause zu kommen?";
				link.l1.go = "Node_237";
			}
			link.l2 = "Vielleicht haben sie das. Wie auch immer, unsere Wege trennen sich jetzt hier. Auf Wiedersehen!";
			link.l2.go = "Node_244";
		break;
		
		case "Node_243":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_244":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_245":
			dialog.text = "Danke, Kapitän. Sie wissen, es ist schwer zu glauben, dass ich endlich zu Hause bin. Bitte, kommen Sie mit mir, ich werde Sie meinen Eltern vorstellen.";
			link.l1 = "Hör zu, "+GetSexPhrase("Schönheit","Liebling")+", Ich habe wirklich keine Zeit dafür. Vielleicht ein anderes Mal?";
			link.l1.go = "Node_246";
		break;
		
		case "Node_246":
			dialog.text = "Wie schade... Nun, leb wohl dann, und möge der Herr über dich wachen. Ich habe nichts, um dich zu belohnen, aber bitte nimm dieses Amulett an.";
			link.l1 = "Danke! Lauf jetzt nach Hause, mach deine Eltern glücklich!";
			link.l1.go = "Node_247";
		break;
		
		case "Node_247":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);		
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "24");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl","sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			CloseQuestHeader("JungleGirl");
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "Node_248":
		break;
		
		case "Node_237":
			dialog.text = "Nun, ich weiß nicht... Vielleicht muss ich auf eine vorbeifahrende Fahrt warten. Aber ich kann dich nicht um Geld bitten.";
			if(makeint(pchar.money)>=5000)
			{
				link.l1 = "Ich verstehe. Also gut, nimm 5000 Pesos. Das sollte genug sein.";
				link.l1.go = "Node_237_1";
			}
			if(makeint(pchar.money)>=25000)
			{
				link.l2 = "Ich verstehe. Gut, nimm 25000 Pesos und geh nach Hause.";
				link.l2.go = "Node_237_2";
			}
			if(makeint(pchar.money)>=35000)
			{
				link.l3 = "Ich verstehe. Also gut, nimm 35000 Pesos. Das sollte genug sein, um die beste Kabine auf dem Schiff zu kaufen.";
				link.l3.go = "Node_237_3";
			}
		break;
		
		case "Node_237_1":
			AddMoneyToCharacter(pchar, -5000);
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			dialog.text = "Danke, "+GetSexPhrase("edler Kapitän","edles Mädchen")+". Ich werde nie vergessen, was du für mich getan hast.";
			link.l1 = "Gute Reise, dann. Leb wohl...";
			link.l1.go = "Node_238";
			pchar.GenQuest.EncGirl = "EncGirlFack_GetMoney";
		break;
		
		case "Node_237_2":
			AddMoneyToCharacter(pchar, -25000);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			dialog.text = "Danke, "+GetSexPhrase("edler Kapitän","edles Mädchen")+". Ich werde nie vergessen, was du für mich getan hast.";
			link.l1 = "Gute Reise, dann. Lebewohl...";
			link.l1.go = "Node_238";
		break;
		
		case "Node_237_3":
			AddMoneyToCharacter(pchar, -35000);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			dialog.text = "Danke, "+GetSexPhrase("edler Kapitän","edles Mädchen")+". Ich werde niemals vergessen, was du für mich getan hast.";
			link.l1 = "Gute Reise, dann. Lebewohl...";
			link.l1.go = "Node_238";
		break;
		
		case "Node_238":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			if(pchar.GenQuest.EncGirl == "EncGirlFack_GetMoney") 
			{
				AddSimpleRumour(RandPhraseSimple("Have you heard? A whore was trying to sneak on board of a ship without documents, but she was caught and taken back to the brothel. They say she owed the madam quite a sum.",  
				"Have you heard? A whore without documents was caught at the port. They say she had cleaned out madam's coffers before attempting to flee from the brothel. I say, that source of filth and thievery must have been closed off long ago. Our kids are even seeing this and what can they learn from such an example?"), sti(pchar.GenQuest.EncGirl.nation), 3, 1);
			}
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_250":
			dialog.text = "Versauen Sie mir nicht das Leben, Kapitän! Mein Vater will, dass ich den Sohn des Wucherers heirate, diesen dreckigen Milchbart... nur weil sein Vater eine Menge Geld in seinen Truhen hat! Nun, ich würde lieber im Dschungel bleiben, um von wilden Tieren gefressen zu werden, als eine lebenslange Haftstrafe mit ihm zu nehmen!";
			link.l1 = "Was ist das Problem mit Ihrer Ehe, "+GetSexPhrase("Schönheit","Schatzi")+"? Halte denjenigen fest, der dich heiraten möchte, und sei glücklich. Nach einiger Zeit würdest du gerne diesen Milchbart heiraten, aber es könnte zu spät sein...";
			link.l1.go = "Node_251";
		break;
		
		case "Node_251":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = "Nein! Nein, Kapitän, ich liebe "+pchar.GenQuest.EncGirl.sLoverId+" und ich werde keinen anderen Mann heiraten! Und mein Vater will nichts hören! Er sagt, dass "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+" ist nur ein Besucher hier, also wird er hier nie einen Job finden, und er ist dazu bestimmt, in Armut zu sterben, und ich mit ihm! Und ich würde mit ihm bis ans Ende der Welt gehen, nur um an seiner Seite zu sein! Bring mich zu ihm, ich flehe dich an!";
			link.l1 = "In Ordnung, lass uns gehen. Ich werde wohl herausfinden, was ich mit dir anfangen soll...";
			link.l1.go = "Node_252";
		break;
		
		case "Node_252":
			Diag.TempNode = "Node_253";
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "9");
			AddQuestUserData("JungleGirl","sText", pchar.GenQuest.EncGirl.FatherGen);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sLover", pchar.GenQuest.EncGirl.sLoverId); 
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_253":
			Diag.TempNode = "Node_253";
			dialog.text = "Kapitän, Sie versprachen, mich zur Ansiedlung von "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+".";
			link.l1 = RandPhraseSimple("Ich erinnere mich.","Mach dir keine Sorgen, ich bringe dich dorthin.");
			link.l1.go = "exit";			
		break;
		
		case "Node_260":
			chrDisableReloadToLocation = false;
			if(rand(1) == 0)
			{
				dialog.text = RandPhraseSimple("Danke, "+GetSexPhrase("Kapitän","junge Dame")+", noch einmal. Wirklich, ich bin Ihnen so sehr verpflichtet.","Vielen Dank, "+GetSexPhrase("Kapitän","junge Dame")+". Ich habe keine Ahnung, was ich ohne deine Hilfe tun würde.");
				link.l1 = RandPhraseSimple("Das sollte dir eine Lehre sein. Also gut, viel Glück...","Nächstes Mal solltest du vorsichtiger sein... Jetzt lauf nach Hause, ich habe Dinge zu erledigen.");
				link.l1.go = "Node_260End";
				link.l2 = "Wie konntest du so unvorsichtig sein? Warum bist du alleine in den Dschungel gegangen?";
				link.l2.go = "Node_13";
			}
			else
			{
				dialog.text = "Ach, "+GetSexPhrase("Kapitän","junge Dame")+", ich habe wirklich keine Ahnung, wie ich Ihnen danken soll.";
				link.l1 = "Es war nichts. Immer froh zu helfen...";
				link.l1.go = "Node_261";
			}
		break;
		
		case "Node_260End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");			
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_261":
			dialog.text = "Können Sie mich zur Taverne bringen? Ich muss auf meine Tante warten und mich ausruhen, dieses 'Abenteuer' hat meine ganze Energie verbraucht...";
			link.l1 = "Nein, "+GetSexPhrase("Schönheit","Schatz")+", das ist sicherlich genug für mich. Ich habe viel zu tun.";
			link.l1.go = "Node_262";
			link.l2 = ""+GetSexPhrase("Oh, Frauen! Gibt es etwas, das sie ohne die Hilfe eines Mannes tun können?","Warum bist du so hilflos?")+"Lass uns gehen...";
			link.l2.go = "Node_263";
		break;
		
		case "Node_262":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "", "", -1.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_263":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";					
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
				
		case "ThanksForHelp_1":
			Diag.TempNode = "ThanksAgain";
			if(makeint(Pchar.reputation.nobility) >= 80)
			{
				dialog.text = "Ich habe etwas Geld... Bitte, akzeptiere es als Zeichen meiner Dankbarkeit!";
				Link.l1 = "Danke. Sei das nächste Mal vorsichtiger.";
				Link.l1.go = "exit";
			}
			else 
			{
				if(hrand(1) == 0)
				{
					dialog.text = "Ich werde jedem erzählen, dass du mich gerettet hast! Alle sollen es wissen, "+GetSexPhrase("was für ein tapferer und mutiger Mann du bist","was für eine mutige und tapfere Dame Sie sind")+"!";
					Link.l1 = "Danke. Und jetzt solltest du nach Hause gehen.";
					Link.l1.go = "exit";
				}
				else
				{
					addMoneyToCharacter(Pchar, makeint(PChar.rank)*100);
					dialog.text = "Ich habe etwas Geld... Bitte, nimm es als Zeichen meiner Dankbarkeit!";
					Link.l1 = "Danke. Versuche nächstes Mal vorsichtiger zu sein.";
					Link.l1.go = "exit";
				}
			}
		break;

		case "ThanksAgain":
            Diag.TempNode = "ThanksAgain";
            dialog.text = "Ich werde jedem erzählen, dass du mich gerettet hast! Lass es jeder wissen, "+GetSexPhrase("was für ein tapferer und mutiger Mann du bist","was für eine tapfere und mutige Dame Sie sind")+"!";
			Link.l1 = "Danke. Und jetzt solltest du nach Hause gehen.";
			Link.l1.go = "exit";
		break;
	}
}
