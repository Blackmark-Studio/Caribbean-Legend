// Джессика Роуз - нежить и супербосс
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Kérsz valamit?";
			link.l1 = "Nem, semmi.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// бой на рифе
		case "reef":
			PlaySound("Voice\English\saga\Jessica Rose-06.wav");
			dialog.text = "Te! Te hoztad ide! Ô az ô húsa és vére! Ô az ô húsa és vére! A szajha lánya eljött az anyja sírjához! Meg fog halni! És te nem fogod tudni megállítani! Ne állj Jessica útjába! A bosszú legyen az enyém!";
			link.l1 = "...";
			link.l1.go = "reef_1";
		break;
		
		case "reef_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "stage_1":
			PlaySound("Voice\English\saga\Jessica Rose-07.wav");
			dialog.text = "Ha! Nem árthatsz nekem!\n A levegô, a víz, a föld, a tûz - megparancsolom nektek, hogy segítsetek nekem!\n Hadd támadjanak fel a holtak, hadd égjen a tûz, hadd ôrizze a víz a hidat, hadd vegyen szárnyaira a szél, és dobjon le a földre!\nHave fun!!!!";
			link.l1 = "...";
			link.l1.go = "stage_1_exit";
		break;
		
		case "stage_1_exit":
			DialogExit();
			LAi_SetActorType(pchar);
			CreateLocationParticles("blast_inv", "quest", "top", 1.6, 0, 0, "");
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "goto", LAi_FindFarFreeLocator("goto", locx, locy, locz));
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaFirstKick_2", 3.5);
		break;
		
		case "stage_2":
			PlaySound("Voice\English\saga\Jessica Rose-08.wav");
			dialog.text = "Ha! Nem tudsz bántani!\nHadd támadjon még több halott, hadd égesse a tûz a követ, hadd ragadjon fel és dobjon le a szél, hadd szívja magába a föld az erôdet!\nÉrvezd!!!";
			link.l1 = "...";
			link.l1.go = "stage_2_exit";
		break;
		
		case "stage_2_exit":
			DialogExit();
			LAi_SetActorType(pchar);
			CreateLocationParticles("blast_inv", "quest", "rock", 1.6, 0, 0, "");
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.BladePenalty = 30;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaSecondKick_2", 3.5);
		break;
		
		case "stage_3":
			PlaySound("Voice\English\saga\Jessica Rose-07.wav");
			dialog.text = "Ha! Engem nem tudsz bántani!\nMéreg borítsa be lángpengés kardomat, a szél öleljen ölelésébe, a víz igya el fürgeségedet!\nDögölj meg! Ha-ha-ha!";
			link.l1 = "...";
			link.l1.go = "stage_3_exit";
		break;
		
		case "stage_3_exit":
			DialogExit();
			npchar.viper = true;
			TakeNItems(npchar, "potion2", 3);
			LAi_SetActorType(pchar);
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.EnergyPenalty = 2;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "quest", "bridge2");
			LAi_ActorTurnToLocator(pchar, "quest", "bridge1");
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaThirdKick_2", 3.5);
		break;
		
		case "stage_4":
			PlayStereoOGG("music_shore");
			sld = characterFromId("Svenson");
			dialog.text = "Elég volt... Elfáradtam. Legyôztek... Szánjátok meg a szerencsétlen Jessica sorsát!";
			link.l1 = "Persze... Megkímélem szegény lelkedet ennek a holttestnek a súlyától!";
			link.l1.go = "exit_battle";
			if (CheckAttribute(sld, "quest.jessika_peace")) // выслушал историю Джессики
			{
				link.l2 = "Ismerem a történeted, Jessica. És sajnálom, hogy az életed ilyen szomorú volt és így ért véget. Beszélni akarsz velem, ugye? Nos, megpróbálom elfelejteni, hogy nemrég megpróbáltál megölni, és meghallgatlak, bár nem lesz könnyû dolgom...";
				link.l2.go = "exit_talk";
			}
		break;
		
		case "exit_battle":
			DialogExit();
			SetMusic("music_teleport");
			DeleteAttribute(npchar, "viper");
			LAi_SetImmortal(npchar, false);
			npchar.chr_ai.hp = stf(npchar.chr_ai.hp)+100;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_JessikaDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.JessSeekTreatment = 0;
			LAi_LocationDisableOfficersGen(pchar.location, false);//офицеров пускать
		break;
		
		case "exit_talk":
			dialog.text = "Köszönöm... Már tudsz Beatrice Sharpról és Lawrence-rôl... az én Lawrence-emrôl. Ôt habozás nélkül megöltem, de ôt nem tudtam megölni. Én nem tudtam megtenni, de ô igen. Jessica meghalt...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Reef");
			NextDiag.TempNode = "exit_talk_0";
		break;
		
		case "exit_talk_0":
			dialog.text = "... de a véreskü, amelyet egy szörnyû esküvel kötöttek össze, még mindig nem teljesült. Az eskü ereje az indián mágiából ered. Feltámasztotta a hullát a sírjából.\nA gyûlölet sivataggá változtatta a lelkemet. Mindenkit, aki erre a zátonyra érkezett, megöltem a kezem által, és holttestük a bábjaimmá vált. Nem kérhetek mástól segítséget, mint attól, aki legyôzött engem...";
			link.l1 = "És mit tehetek érted? Az egyetlen dolog, amit tehetek, hogy megkíméllek a szenvedéstôl...";
			link.l1.go = "exit_talk_1";
		break;
		
		case "exit_talk_1":
			PlaySound("Voice\English\saga\Jessica Rose-03.wav");
			dialog.text = "Segíts nekem... Vigyél el hozzá.";
			link.l1 = "Lawrence Beltrope-nak? És hogyan kellene ezt megtennem? A legénységem vagy elmenekül, amint meglátja magát, vagy pedig megbánás nélkül megégeti. Egyébként még mindig képes vagy lemészárolni az embereimet, és 'control' them...";
			link.l1.go = "exit_talk_2";
		break;
		
		case "exit_talk_2":
			dialog.text = "Nem fognak látni engem. De te igen. Már biztosan megértetted, hogy olyan erôkkel rendelkezem, amelyek az élôk számára elérhetetlenek. De nem léphetek a hajójukra az engedélyük nélkül. Vigyetek hozzá.\nNem maradok sokáig veletek. És nem fogom bántani a népedet. Szállj le velem a jamaicai Portland-öbölben éjfélkor, a következô éjjel újra találkozunk, és megkapod, amit itt akartál találni.";
			link.l1 = "Honnan tudod, hogy miért vagyok itt?";
			link.l1.go = "exit_talk_3";
		break;
		
		case "exit_talk_3":
			PlaySound("Voice\English\saga\Jessica Rose-01.wav");
			dialog.text = "Sok mindent tudok. Többet, mint az élôk. Láttam ôt... Szükséged van egy dokumentumra, és meg fogod kapni. Még többet is kapsz, adok neked valamit hozzá. Vigyél el hozzá...";
			link.l1 = "Hm. Nem tetszik a vérszomjas szándékod Helennel szemben. Ne merészelj hozzáérni. Végül is, ô nem felelôs az anyja tetteiért.";
			link.l1.go = "exit_talk_4";
		break;
		
		case "exit_talk_4":
			dialog.text = "Legyôztél engem. Nem fogom bántani ôt... Ígérem.";
			link.l1 = "Még nincs vége. Megszabadítasz a számtalan átkodtól? Bevallom, nem tetszik a gondolat, hogy örökké velük kell élnem...";
			link.l1.go = "exit_talk_5";
		break;
		
		case "exit_talk_5":
			dialog.text = "Ez nem ilyen egyszerû... Mikor találkozunk Portland Cove-ban, miután én... Elmondom neked, hogyan gyógyítsd meg magad.";
			link.l1 = "Miután mit? Hogy érted ezt?";
			link.l1.go = "exit_talk_6";
		break;
		
		case "exit_talk_6":
			dialog.text = "Miután találkoztam vele.";
			link.l1 = "Ó, nem lesz boldog. El tudom képzelni. Rendben, foglaljuk össze: elôször is, megígéred, hogy senki sem lát meg, másodszor, nem bántod a legénységemet, harmadszor, még csak nem is gondolsz Helénára, negyedszer, megadod nekem, amit keresek, és ötödször, meggyógyítasz az átkaidtól. Igazam van?";
			link.l1.go = "exit_talk_7";
		break;
		
		case "exit_talk_7":
			dialog.text = "Majdnem. Nem foglak meggyógyítani, de megmondom, hogyan. Neked magadnak kell megtenned.";
			link.l1 = "Rendben. Akkor megegyeztünk. Engedélyezem, hogy a hajómra szállj.";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Reef2");
			NextDiag.TempNode = "exit_talk_8";
		break;
		
		case "exit_talk_8":
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			dialog.text = "";
			link.l1 = "Hé! Hol vagy? Eltûntem...";
			link.l1.go = "exit_talk_9";
		break;
		
		case "exit_talk_9":
			DialogExit();
			LAi_group_Delete("EnemyFight");
			pchar.quest.Saga_JessFire.over = "yes"; 
			pchar.quest.Saga_JessFire1.over = "yes"; 
			pchar.quest.Saga_JessFire2.over = "yes";
			ref chr = &Locations[FindLocation(pchar.location)];
			DeleteAttribute(chr, "hell_fire_1");
			DeleteAttribute(chr, "hell_fire_2");
			DeleteAttribute(chr, "hell_fire_3");
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Shadows", "9");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.Saga.JessOnShip = "true"; // атрибут на отрицательные последствия
			pchar.quest.Saga_Jessika_Travel.win_condition.l1 = "Hour";
			pchar.quest.Saga_Jessika_Travel.win_condition.l1.start.hour = 0.00;
			pchar.quest.Saga_Jessika_Travel.win_condition.l1.finish.hour = 2.00;
			pchar.quest.Saga_Jessika_Travel.win_condition.l2 = "location";
			pchar.quest.Saga_Jessika_Travel.win_condition.l2.location = "shore36";
			pchar.quest.Saga_Jessika_Travel.function = "Saga_JessikaOnJamaica";
			NextDiag.CurrentNode = "shore";
			npchar.greeting = "jessika_2";
			LAi_LocationDisableOfficersGen(pchar.location, false);//офицеров пускать
			LAi_LocationDisableOfficersGen("shore36", true);//офицеров не пускать в бухту Портленд
		break;
		
		case "shore":
			dialog.text = "Megtartottad a szavadat - Jamaikán vagyunk. Gyere ide holnap este és teljesítem az ígéretemet. Viszontlátásra.";
			link.l1 = "Ég veled...";
			link.l1.go = "shore_1";
		break;
		
		case "shore_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Saga.JessOnShip");
			DeleteAttribute(npchar, "SaveItemsForDead");
			DeleteAttribute(npchar, "DontClearDead");
			LAi_SetActorType(npchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Shadows", "10");
			SetFunctionTimerCondition("Saga_JessikaShoreWait", 0, 0, 1, false);
			NextDiag.CurrentNode = "shore_2";
			npchar.greeting = "jessika_3";
		break;
		
		case "shore_2":
			dialog.text = "Vége, "+pchar.name+"...";
			link.l1 = "Hogy érti ezt?";
			link.l1.go = "shore_3";
		break;
		
		case "shore_3":
			dialog.text = "Vége... Tessék, vedd el, ez az, amit kerestél. Ez a riválisom levele, vele együtt temették el. Jól megmaradt. Megbocsátottam neki, és nincs többé gyûlölet a lelkemben.";
			link.l1 = "Találkoztál vele? Lawrence-szel?";
			link.l1.go = "shore_4";
		break;
		
		case "shore_4":
			GiveItem2Character(pchar, "letter_beatriss"); // дать письмо
			AddQuestRecordInfo("Letter_beatriss", "1");
			dialog.text = "Igen. Az utolsó dolog, amit életében érzett, a rémület volt. Nem sajnálom ôt.";
			link.l1 = "Isten bocsásson meg bûnös lelkének... Úgy tûnik, soha nem fogok találkozni vele.";
			link.l1.go = "shore_5";
		break;
		
		case "shore_5":
			dialog.text = "Semmi értékeset nem vesztettél el. Nagyon rossz ember volt. Most már el kell búcsúznunk egymástól, itt már nincs mit tennem. A fogadalmam teljesült, és a varázslat elvesztette erejét. Ígértem neked egy ajándékot. Tessék. Ez az én Flamberge-em. Már nincs rá szükségem. Ez a penge egyedi, ennél jobbat sehol a világon nem találsz.";
			link.l1 = "Köszönjük...";
			link.l1.go = "shore_6";
		break;
		
		case "shore_6":
			RemoveAllCharacterItems(npchar, true);
			GiveItem2Character(pchar, "blade_25");
			PlaySound("interface\important_item.wav");
			dialog.text = "Most pedig rólad. Menjetek Bridgetownba, a helyi templomba, hogy feloldjátok az átkaimat. Ott találsz majd egy papot. Ô személyesen ismert engem. Beszélj vele, és megmondja, mit kell tenned. Készíts húsz gyertyát, szükséged lesz rájuk.";
			link.l1 = "Biztos vagy benne, hogy meg fog gyógyítani?";
			link.l1.go = "shore_7";
		break;
		
		case "shore_7":
			dialog.text = "Te magad fogod megtenni. Isten vezetni fog téged. Légy biztos benne. Minden rendben lesz.";
			link.l1 = "Rendben, azonnal elhajózom Barbadosra. És most mi lesz?";
			link.l1.go = "shore_8";
		break;
		
		case "shore_8":
			PlaySound("Voice\English\saga\Jessica Rose-04.wav");
			dialog.text = "És most még egy utolsó dolgot kívánok. Temessétek el a testemet itt, ebben az öbölben, a tenger mellett. Ezt akarom. Talán egy nap majd meglátogatod szegény Jessica sírját. Isten veled, "+pchar.name+", és imádkozz értem...";
			link.l1 = "Jess?..";
			link.l1.go = "shore_9";
		break;
		
		case "shore_9":
			DialogExit();
			LAi_KillCharacter(npchar);
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("shore36", false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddQuestRecord("Shadows", "11");
			pchar.questTemp.Saga.JessTreatment = "true";
			// вытираем Белтропа
			sld = characterFromId("Beltrop");
			sld.lifeday = 0;
			pchar.questTemp.Saga.Beltrop_die = "true"; // Белтроп убит
			sld = ItemsFromID("letter_jess");
			sld.price = 1; // страницу можно выкладывать 270912 
		break;
		
		case "soul":
			dialog.text = "Felismer engem, kapitány?";
			link.l1 = "Te vagy... te vagy az? De hogyan?";
			link.l1.go = "soul_1";
		break;
		
		case "soul_1":
			dialog.text = "Igen, "+pchar.name+", én vagyok az, Jessica! Legalábbis amikor húsz évvel ezelôtt így néztem ki.";
			link.l1 = "Szóval... meghaltam? De mikor? De hogyan?";
			link.l1.go = "soul_2";
		break;
		
		case "soul_2":
			dialog.text = "Nem vagy halott, "+pchar.name+". Most a hidvégi templomban vagy. Csak... alszol.";
			link.l1 = "Ez csak egy álom? A dolgok túl valóságosnak tûnnek...";
			link.l1.go = "soul_3";
		break;
		
		case "soul_3":
			dialog.text = "Néha elôfordul, "+pchar.name+". Isten meghallgatott téged. Az imáid nem csak téged gyógyítottak meg, hanem az én lelkemet is megtisztították. Köszönöm szépen, "+pchar.name+"! És szeretném kérni, hogy bocsássatok meg nekem azért, ami a zátonyon történt. Ez... nos, csak bocsássatok meg nekem. Nem mehettem el anélkül, hogy ne kértem volna a bocsánatodat.";
			link.l1 = "Megbocsátok neked, Jessica. Tényleg élek?";
			link.l1.go = "soul_4";
		break;
		
		case "soul_4":
			dialog.text = "Igen... Ne aggódj. Ne aggódj. Hamarosan felébredsz. Csak el akartam búcsúzni.";
			link.l1 = "Olyan... gyönyörû vagy!";
			link.l1.go = "soul_5";
		break;
		
		case "soul_5":
			dialog.text = "Szeretsz engem? Igen, volt idô, amikor a Kis-Antillák legjobb kérôi udvaroltak nekem, és az Isla Tesoro minden harmadik kalóza kész volt párbajozni értem.";
			link.l1 = "De neked mindig csak egy kellett... Eh, gyömbér talizmán! Mondd csak, miért lettél ilyen?";
			link.l1.go = "soul_6";
		break;
		
		case "soul_6":
			dialog.text = "A dühöm miatt. A gyûlöletem miatt. Mert képtelen vagyok megérteni, megbocsátani és felejteni. Kezdhettem volna új életet, de inkább az ostoba és értelmetlen bosszúállásnak szenteltem magam. Te felszabadítottál engem. Köszönöm, "+pchar.name+"...";
			link.l1 = "Nagyon sajnálom az életed...";
			link.l1.go = "soul_7";
		break;
		
		// здесь проверяем Мэри
		case "soul_7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{ // Мэри-офицер
				dialog.text = "Ne... Még mindig megvan a gyömbér talizmánod...";
				link.l1 = "A micsodám?";
				link.l1.go = "mary_1";
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CheckAttribute(pchar, "questTemp.LSC.marywait"))
			{ // Мэри осталась на острове
				dialog.text = "Ne... Még mindig megvan a gyömbér talizmánod...";
				link.l1 = "A micsodám?";
				link.l1.go = "mary_3";
				break;
			}
			dialog.text = "Ne... Gondolj a szomorú tapasztalataimra, és ne ismételd meg a hibáimat. És ne hagyd, hogy a szeretteid is megtegyék.";
			link.l1 = "Megfontolom, és biztosan nem követem el ugyanazokat a hibákat...";
			link.l1.go = "soul_8";
		break;
		
		case "mary_1":
			dialog.text = "Gondolkodj egy kicsit. A te hajódon van.";
			link.l1 = "Mary?!";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "Igen. Ô a legjobb, aki valaha is lesz az életedben. Emlékezz erre. A szeretete tiszta, az odaadása végtelen. Bátor, fiatal, de kétségbeesett és tapasztalatlan. Sok mindent nem ért. Vigyázz rá, védd meg, és ne hagyd, hogy bárki is közétek álljon. Ô a te talizmánod...";
			link.l1 = "I... Soha nem hagyom el ôt, és megvédem minden veszélytôl.";
			link.l1.go = "soul_8";
		break;
		
		case "mary_3":
			dialog.text = "Egy furcsa szigeten van, ami halott hajókból áll... Nincs ott egyedül, de magányos. Minden reggele azzal kezdôdik, hogy rád gondol, minden nap érted imádkozik, minden éjjel fény gyúl a kabinjában, és a párnája nedves a könnyeitôl...";
			link.l1 = "Mary...";
			link.l1.go = "mary_4";
		break;
		
		case "mary_4":
			dialog.text = "Egy lány van köztetek. Annak a nônek a lánya, aki egyszer közém és Lawrence közé állt. A talizmánod sorsa a te kezedben van. Nem tudnak együtt élni, ahogy én és Beatrice sem tudtunk.";
			link.l1 = "Honnan tudod ezt?";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "A másik oldal... Ez sokat mutat... A te döntésed, de ne feledd: Mary a legjobb, akit valaha is kaphatsz az életedben. A szeretete tiszta, az odaadása végtelen. Bátor, fiatal, de kétségbeesett és tapasztalatlan. Sok mindent nem ért. Szüksége van a védelmedre, a gondoskodásodra és a szeretetedre. Ô a te talizmánod.";
			link.l1 = "Ezt figyelembe fogom venni. Biztosan meg fogom tenni...";
			link.l1.go = "soul_8";
		break;
		
		case "soul_8":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) sTemp = "";
			else sTemp = "Ami pedig Beatrice lányát illeti, tudd meg, hogy az érte tett nemes cselekedeteid értékeletlenek maradnak. Hamarosan a saját szemeddel fogod látni. Légy óvatos vele. Well...\n";
			dialog.text = ""+sTemp+"Mennem kell. Itt az ideje elbúcsúzni... Ezúttal tényleg. Ne feledkezz meg Jessicáról, és próbáld meg néha meglátogatni a sírját... Csak te tudod, hol van.";
			link.l1 = "Persze, Jess. Meglátogatom, és imádkozni fogok érted.";
			link.l1.go = "soul_9";
		break;
		
		case "soul_9":
			dialog.text = "Köszönöm. Viszlát, "+pchar.name+"! Viszontlátásra!";
			link.l1 = "Viszlát, Jessica...";
			link.l1.go = "soul_10";
		break;
		
		case "soul_10":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_JessikaSoul_4", -1);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
