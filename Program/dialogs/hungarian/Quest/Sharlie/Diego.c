// Диего де Монтойя
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Van valami, amit szeretnél?";
			link.l1 = "Nem, semmit.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "patrol":
			dialog.text = TimeGreeting()+", "+GetFullName(npchar)+", A San Jose-i járôrszolgálat vezetôje. Üzenetet kaptunk a város külterületén tapasztalt gyanús viselkedésrôl. Lennének olyan kedvesek, és elmagyaráznák nekünk, hogy kik maguk és mire készülnek?";
			link.l1 = "Kapitány "+GetFullName(pchar)+", senor officer. Vincento inkvizítor atya felhatalmazása és közvetlen utasításai alapján vagyok itt. Itt van egy dokumentum, amely megerôsíti a felhatalmazásomat.";
			link.l1.go = "patrol_1";
		break;
		
		case "patrol_1":
			dialog.text = "Rendben... Minden rendben van. Rendesen kitöltve, az inkvizítor aláírásával. Elnézést kérek a gyanakvásomért. Mit keres a világítótoronyban?";
			link.l1 = "Nem vagyok felhatalmazva, hogy ilyen kérdésekre válaszoljak. Ha valóban érdekli az inkvizítornak végzett munkám célja, azt javaslom, hogy közvetlenül hozzá forduljon Santiagóban a tisztázás érdekében. Ön tiszt, bizonyára ismeri a katonai és szolgálati titkokat. Csak annyit mondhatok, hogy egy spanyol hajóroncs körülményeit vizsgálom.";
			link.l1.go = "patrol_2";
		break;
		
		case "patrol_2":
			dialog.text = "Még egyszer elnézést kérek, uram. Nem merem tovább feltartani... á, egy pillanat! Csak nem egy hideg acél pengéjét láttam az imént, vagy csak képzelôdtem? Milyen érdekes tôröd van! Megmutatná nekem?";
			link.l1 = "Ne felejtsd el visszaadni! Nagyon fontos nekem.";
			link.l1.go = "patrol_3";
		break;
		
		case "patrol_3":
			dialog.text = "Dios mio! Ismerem ezt a tôrt, láttam az egyik könyvtári könyvben! Ez maga Cortes tôrje! Itt van ráírva... Monsieur, kérem, ne utasítsa vissza. Adja ide ezt a tôrt! Gyûjtöm az ôsi és személyes fegyvereket, és ez egyszerûen egy hihetetlen példány. Jól megfizetek érte.";
			link.l1 = "Senor, ez a tôr nem eladó. Ajándékba kaptam, és nem akarom eladni senkinek. Adja vissza, kérem.";
			link.l1.go = "patrol_4";
		break;
		
		case "patrol_4":
			dialog.text = "Még ötszáz aranydublonnal sem lenne elégedett? Az rengeteg pénz. Vehetnél belôle egy hajót!";
			link.l1 = "Nem. Nekem már van hajóm, és ez a tôr egyedi. Nem fogom eladni.";
			link.l1.go = "patrol_5";
		break;
		
		case "patrol_5":
			dialog.text = "Eh, ez nagyon rossz... Rendben, vegye el az értékeset. Nem merlek tovább zavarni. Sok szerencsét!";
			link.l1 = "Minden jót, biztos úr.";
			link.l1.go = "patrol_6";
		break;
		
		case "patrol_6":
			DialogExit();
			AddQuestRecord("Guardoftruth", "42");
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "GuardOT_ClearMayakPatrol", 12.0);
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("GOT_spamayaksold_"+i);
				sld.lifeday = 0;
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 10.0);
			}
		break;
		
		case "shore":
			PlaySound("Voice\English\Sharlie\Diego De Montoya.wav");
			dialog.text = "Elég volt! Beszélni akarok vele...";
			link.l1 = "Szóval, látom, hogy Diego de Montoya személyesen áll elôttem... De bocsásson meg, senor. Már találkoztunk, nem igaz? Ó, igen, így van. Trinidadban, a helyi világítótoronyban. De biztos vagyok benne, hogy ott máshogy hívta magát...";
			link.l1.go = "shore_1";
		break;
		
		case "shore_1":
			dialog.text = "A memóriája jól szolgálja önt, uram. Nos, nem maga az egyetlen, aki képes intrikákat szítani és háborúkat vívni a színfalak mögött. Jól értesültem arról, hogy múlhatatlanul vágyik arra, hogy lásson engem. Nos, úgy tûnik, a kívánsága valóra vált.";
			link.l1 = "Nem éppen ilyen találkozásra számítottam, senor.";
			link.l1.go = "shore_2";
		break;
		
		case "shore_2":
			dialog.text = "Nos, ez az, ami. De adok egy esélyt, hogy élve kijusson innen, ha ideadja a tôrét.";
			link.l1 = "A ritkaságok gyûjtése iránti szenvedélye tényleg olyan mélyre küldte a csövekbe, caballero, hogy ilyen jól kitalált csapdát kellett készítenie nekem?  Ó, nem hiszem. Az Igazság Ôrzôje tartja önt fogva, vagy én vagyok messze?";
			link.l1.go = "shore_3";
		break;
		
		case "shore_3":
			dialog.text = "Fogalmam sincs, mirôl beszélsz. A tôrnek vissza kell térnie oda, ahová tartozik, és ennyit kell tudnod. Nem akartad odaadni az aranyért, ezért most a saját életedért fogod odaadni.";
			link.l1 = "Tényleg azt hiszi, senor, hogy elhiszem, amit az imént mondott? Már eldöntötte, hogy nem hagyom el ezt az öblöt, ugye?";
			link.l1.go = "shore_4";
		break;
		
		case "shore_4":
			dialog.text = "És mi van, ha a szavamat adom?";
			link.l1 = "A szó a 'békaevô'? Hm...";
			link.l1.go = "shore_5";
		break;
		
		case "shore_5":
			dialog.text = "Monsieur, adok egy utolsó esélyt. Vagy átadja a tôrt, ami engem érdekel, vagy pár percen belül kifosztom a holttestét. Az ellenállás hiábavaló, elsöprô létszámfölényben vagyunk.";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.SanAntonio")) link.l1 = "Meglepett engem, senor, az biztos. Tényleg azt hiszi, hogy olyan ostoba hülye vagyok, hogy csak úgy beledugnám a fejem egy cápa állkapcsába anélkül, hogy a szigonyomat elkapnám? Srácok, öljétek meg ôket!";
			else link.l1 = "Az igazi hatalom nem a számokban rejlik, hanem az ügyességben, senor!";
			link.l1.go = "shore_6";
		break;
		
		case "shore_6":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto5", "none", "", "", "", 10.0);
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.SanAntonio"))
			{
				PlaySound("interface\abordage_wining.wav");
				PlaySound("interface\abordage_wining.wav");
				for(i=1; i<=10; i++)
				{
					sld = characterFromId("GuardOT_Oursoldier_"+i);
					LAi_SetWarriorType(sld);
					ChangeCharacterAddressGroup(sld, "Shore15", "reload", "reload1_back");
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			sld = CharacterFromID("spa_baseprisoner");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for(i=1; i<=13; i++)
			{
				sld = characterFromId("GOT_spashore_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_DiegoShoreGuardDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
