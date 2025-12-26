void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Mit szeretne?";
			link.l1 = "Semmi.";
			link.l1.go = "exit";
		break;

		//--> Встреча
		case "DiegoDeLanda_Meeting":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "Szomorú történet, nem igaz?";
				link.l1 = "Ki vagy te?";
				link.l1.go = "DiegoDeLanda_Meeting_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
			{
				dialog.text = "Üdvözlöm, kapitány.";
				link.l1 = "Várjon! Már találkoztunk korábban!";
				link.l1.go = "DiegoDeLanda_Meeting_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
			{
				dialog.text = "Egy. Kettô. Három.";
				link.l1 = "Hagyjuk abba ezt az elôadást. Ki vagy te?";
				link.l1.go = "DiegoDeLanda_Meeting_Third_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 4)
			{
				dialog.text = "Four.";
				link.l1 = "Two left?";
				link.l1.go = "DiegoDeLanda_Meeting_Fourth_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 5)
			{
				
			}
			DelLandQuestMark(npchar);
		break;
		
		case "DiegoDeLanda_Meeting_2":
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia"))
			{
				dialog.text = "Tudod, mi a különleges ebben a kriptában? Itt fekszik két lélek, akiket a vér köt össze. Apa és fia de Alameda. Az egyik a bûnösök kezébe került, a másik... hmm, megtalálta az utat az Úrhoz.";
				link.l1 = "Don Fernando naplója hozott ide.";
				link.l1.go = "DiegoDeLanda_SantaMisericordia_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth"))
			{
				dialog.text = "Látta Lady Bishopot? Szomorú sors, nem igaz? De attól tartok, megérdemelte.";
				link.l1 = "Ismeri Elizabeth-et?";
				link.l1.go = "DiegoDeLanda_LadyBeth_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_Memento"))
			{
				dialog.text = "Mortimer Grim.";
				link.l1 = "Ismerte ôt, természetesen?";
				link.l1.go = "DiegoDeLanda_Memento_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_ClockTower"))
			{
				dialog.text = ""+GetCharacterName("Hendrik")+" "+GetCharacterName("van Doorn")+".";
				link.l1 = "Your client?";
				link.l1.go = "DiegoDeLanda_ClockTower_2";
			}
		break;

		case "DiegoDeLanda_Meeting_Third_2":
			dialog.text = "\nThree more. Hatra már mindent tudni fogsz.";
			link.l1 = " Ha most azonnal nem kapok egyértelmû válaszokat, akkor...";
			link.l1.go = "DiegoDeLanda_Meeting_Third_3";
		break;

		case "DiegoDeLanda_Meeting_Third_3":
			dialog.text = "\nJól csinálja, kapitány. Megérdemli, hogy tudja a nevemet. Diego de Landa.";
			link.l1 = " Maga tényleg pap?";
			link.l1.go = "DiegoDeLanda_Meeting_Third_4";
		break;

		case "DiegoDeLanda_Meeting_Third_4":
			dialog.text = "Mindenekelôtt mûvész vagyok. De ne siessük el...";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Meeting_2";
		break;
		//<-- Встреча
		
		//--> Святое Милосердие
		case "DiegoDeLanda_SantaMisericordia_2":
			dialog.text = "Ah... A napló. Figyelemre méltó dolog - az írott szó. Olyan, mint... egy ösvény a sötétben. Oda vezet, ahol a kinyilatkoztatás vár rád. Don Fernando gyakran meglátogatta a plébániánkat. Különösen az elmúlt évben.";
			link.l1 = "A helyi plébánián szolgál? Ismerte Don Fernandót?";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_3";
		break;

		case "DiegoDeLanda_SantaMisericordia_3":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_4";
		break;

		case "DiegoDeLanda_SantaMisericordia_4":
			dialog.text = "Én... figyeltem az útját. És azt a könyvet, amit elvitt. Tudja, mi a különleges benne?";
			link.l1 = "Hogy réginek tûnik.";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_5";
		break;

		case "DiegoDeLanda_SantaMisericordia_5":
			dialog.text = "Régi? Ó, nem. Ez... megvilágosodott. Idôsebb Don de Alameda Bibliája. Minden egyes szó benne olyan, mint egy világítótorony a sötétben. Vegye el. Segítsetek a testvéreiteknek Krisztusban, és akkor talán... ez elvezet titeket valami... nagyobb dologhoz.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		//<-- Святое Милосердие
		
		//--> Леди Бет
		case "DiegoDeLanda_LadyBeth_2":
			dialog.text = "Ó, igen. Szegény asszony. A férje... nem a legkedvesebb ember. Azt mondják, az ô ültetvényei a legtermékenyebbek Barbadoson. És a legkegyetlenebb. Tudja, hány rabszolga hal meg ott havonta? Nemrég agyonvert egy igazi angliai orvost - egy nagyszerû elméjû és tehetséges embert. De az ô sorsa sem sokkal jobb, higgye el nekem.";
			link.l1 = "Úgy tûnik, nagyon jól tájékozott.";
			link.l1.go = "DiegoDeLanda_LadyBeth_3";
		break;

		case "DiegoDeLanda_LadyBeth_3":
			dialog.text = "Az emberek gyónni jönnek hozzám, kapitány. Olyan dolgokat hallok, amiket még a szeretteiknek sem mernek elmondani. A félelmeiket, a bûneiket... a fájdalmukat.";
			link.l1 = "Nem fél az üldöztetéstôl? Nem könnyû egy katolikus papnak angol földön.";
			link.l1.go = "DiegoDeLanda_LadyBeth_4";
		break;

		case "DiegoDeLanda_LadyBeth_4":
			dialog.text = "Az én félelmeim semmi ahhoz képest, amit az ajtó mögött hagytál. És az a kis könyv, amit elvett attól a szerencsétlen nôtôl... Ha a félelemnek lenne alakja, pontosan ilyen lenne.\n"+
		"Jó napot, kapitány.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		
		//<-- Леди Бет
		
		//--> Мементо
		case "DiegoDeLanda_Memento_2":
			dialog.text = "Tigris, tigris, fényesen égô\n"+
			"Éjszakai erdôkben,\n"+
			"Melyik halhatatlan kéz vagy szem\n"+
			"tudná keretbe foglalni félelmetes szimmetriádat?\n"+
			"Persze, hogy ismertem ôt, kapitány. De maga ismerte?";
			link.l1 = "Soha nem találkoztam még tragikusabb sorsú emberrel.";
			link.l1.go = "DiegoDeLanda_Memento_3";
		break;

		case "DiegoDeLanda_Memento_3":
			dialog.text = "Igen, de még nem jöttél rá.\n"+
			"Akkor nem ismerted Grimet. Még akkor sem, amikor a koponyáját a kezedben tartod.";
			link.l1 = "Micsoda?!";
			link.l1.go = "DiegoDeLanda_Memento_4";
		break;

		case "DiegoDeLanda_Memento_4":
			dialog.text = "Nem keresztényi módon kell bánni a halottakkal. Tessék, itt van ez a kis halottvizsgálati utasítás. Ajándék tôlem önnek.\n"+
			"Jó napot, kapitány.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
			SetAlchemyRecipeKnown("blade_SP_3low");	// рецепты от Катласа
			SetAlchemyRecipeKnown("blade_SP_3");
		break;
		
		//<-- Мементо
		
		//--> Башня с часами
		case "DiegoDeLanda_ClockTower_2":
			dialog.text = "Witty, Captain. You were his client, and he was mine.\n"+
			"How alike you are.\n"+
			"You haven't forgotten how you got into the registry, have you? First you helped the glorious city of Willemstad. Only to later drown many of its sons in blood.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_ClockTower_3";
		break;
		
		case "DiegoDeLanda_ClockTower_3":
			dialog.text = "Though Hendrick didn't manage to do the latter. Difficult client, very difficult. Here, for instance. Read it at your leisure — a complete mystery.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_ClockTower_4";
			// получаем документы Маартена
			ClockTower_AddVisserKey();
			
		break;
		
		case "DiegoDeLanda_ClockTower_4":
			dialog.text = "Every person is a building. Want to know what truly drives them? Look into their cellar.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_ClockTower_5";
		break;
		
		case "DiegoDeLanda_ClockTower_5":
			dialog.text = "Here.";
			if (CheckAttribute(pchar, "questTemp.ClockTower_GotHint"))
			{
				link.l1 = "Key to the cellar? I've already been there.";
				link.l1.go = "DiegoDeLanda_ClockTower_6";
			}
			else
			{
				link.l2 = "What's in your cellar?";
				link.l2.go = "DiegoDeLanda_ClockTower_7";
			}
		break;
		
		case "DiegoDeLanda_ClockTower_6":
			dialog.text = "\nThen we have nothing more to discuss, Captain.";
			link.l1 = "Offended? I wonder, what's in your cellar?";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		
		case "DiegoDeLanda_ClockTower_7":
			dialog.text = "\nEvery conversation we have is a step down there, Captain.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
			ClockTower_AddBook_FromDiegoDeLanda(); // получаем ключ от подвала
		break;
		
		//<-- Башня с часами
		
		//--> Прощание
		case "DiegoDeLanda_Leaving":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving");
		break;
		
		case "DiegoDeLanda_Leaving_1":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "Mondja... Miért? Ez veszélyes és ostoba dolog volt. Mi hajtja magát, kapitány? Mi a tüze?";
				link.l1 = "Semmi köze hozzá.";
				link.l1.go = "DiegoDeLanda_leaving_First_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
			{
				dialog.text = "Másodszor.";
				link.l1 = "Legutóbb rejtvényekben beszéltél. Megint megteszi?";
				link.l1.go = "DiegoDeLanda_leaving_Second_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
			{
				dialog.text = "...";
				link.l1 = "Várjon, de Landa. Nem hagyhatom, hogy csak úgy elvegye és elmenjen.";
				link.l1.go = "DiegoDeLanda_Leaving_Third_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 4)
			{
				dialog.text = "Nothing but hints, theatrics, and no action\n"+
				"On my part, at least. You've had plenty of action.";
				link.l1 = "I have an idea how to fix that.";
				link.l1.go = "DiegoDeLanda_Leaving_Fourth_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 5)
			{
				
			}
		break;
		
		case "DiegoDeLanda_Leaving_First_2": // Первое прощание
			dialog.text = "Nem értem. A többiek - igen. De magát nem. Még nem.";
			link.l1 = "A többiek?";
			link.l1.go = "DiegoDeLanda_Leaving_First_3";
		break;

		case "DiegoDeLanda_Leaving_First_3":
			dialog.text = "Az egyik például az igazságot keresi. Egy másik... a halál sötét vizeinek megszállottja. Az emberek olyan könnyen elveszítik magukat a vágyaikban. Nem gondolja?";
			link.l1 = "Maga egy furcsa pap, atyám.";
			link.l1.go = "DiegoDeLanda_Leaving_First_4";
		break;

		case "DiegoDeLanda_Leaving_First_4":
			dialog.text = "...";
			link.l1 = "Mennem kell.";
			link.l1.go = "DiegoDeLanda_Leaving_First_5";
		break;

		case "DiegoDeLanda_Leaving_First_5":
			dialog.text = "Hát persze. A munkája még csak most kezdôdik, kapitány.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;

		case "DiegoDeLanda_leaving_Second_2": // Второе прощание
			dialog.text = "\nAz igazi rejtély elôttem áll. Már összegyûjtöttél két... ereklyét. Szeretsz ilyeneket gyûjteni? Gyûjtô vagy?";
			link.l1 = "Honnan tudja?";
			link.l1.go = "DiegoDeLanda_leaving_Second_3";
		break;

		case "DiegoDeLanda_leaving_Second_3":
			dialog.text = "Trófeavadász?";
			link.l1 = "Megismétlem a kérdésem: honnan tudod?";
			link.l1.go = "DiegoDeLanda_leaving_Second_4";
		break;
		
		case "DiegoDeLanda_leaving_Second_4":
			dialog.text = "Izgalomkeresô?";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving_Second_5";
		break;

		case "DiegoDeLanda_leaving_Second_5":
			dialog.text = "\nAh. Természetesen. Természetesen. Nos, kapitány, akkor nem tartom fel.";
			link.l1 = "Várjon, atyám. Még mindig nem válaszolt a kérdésemre.";
			link.l1.go = "DiegoDeLanda_leaving_Second_6";
		break;

		case "DiegoDeLanda_leaving_Second_6":
			dialog.text = "Ó, kapitány. Nem tehetem. Néha a válaszok jobban sebeznek, mint a tudatlanság. Menjen békével. És vigyázzon a gyûjteményére... a trófeáira. Még jól jöhetnek az elôttünk álló úton.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;

		case "DiegoDeLanda_Leaving_Third_2": // Третье прощание
			dialog.text = "Jöjjön, kapitány. Hát nem érdekes ez önnek? Nem érzi jól magát? Van elég trófeája?\n"+
			"Ez a maga tüze, kapitány. Kíváncsi vagy arra, hogy mi következik. Imádod a szép hajókat és a lenyûgözô csecsebecséket.\n"+
			"Egyszerûen nem tudsz nem gyûjteni mindet.\n"+
			"\n"+
			"Most rögtön lelôhetsz.";
			link.l1 = "Micsoda?!";
			link.l1.go = "DiegoDeLanda_Leaving_Third_3";
		break;

		case "DiegoDeLanda_Leaving_Third_3":
			dialog.text = "Menjen csak. De akkor nem fogsz mindent megtanulni, és nem fogod megszerezni a teljes trófeakészletet. Bár így is megkapod az összes hajót...\n"+
			"Jó napot, kapitány.";
			link.l1 = "(Engedd el!)";
			link.l1.go = "DiegoDeLanda_Leaving_End";
			link.l2 = "(Lôdd le!)";
			link.l2.go = "DiegoDeLanda_Leaving_Shoot";
		break;
		
		case "DiegoDeLanda_Leaving_Fourth_2": // Четвёртое прощание
			dialog.text = "\nToo late, Captain. You had your chance to shoot me. And what a chance! On the count of three: one, two, three... and nothing. But don't worry. On six, I'll give you action. Not much longer now.\n"+
			"Good day, Captain.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;
		
		case "DiegoDeLanda_Leaving_End":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving_End");
		break;
		
		case "DiegoDeLanda_Leaving_Shoot":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving_Shoot");
		break;
		
		
		//<-- Прощание
	}
} 
