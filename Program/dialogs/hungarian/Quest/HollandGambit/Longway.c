// китаец Лонгвэй, подручный Роденбурга
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
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
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Chuanzhang. A nevem Longway. Longway átadja a hajóját a parancsnokságod alá. Longway is a te parancsnokságod alá tartozik. Rodenburg parancsára.";
			link.l1 = "Üdvözletem, Longway. Charles de Maure, szolgálatára. Van valami nyom a Jacob van Berg likvidálására irányuló akcióról?";
			link.l1.go = "Longway_friend";
			link.l2 = "Örülök, hogy látom, Longway. A nevem Charles de Maure. Nincs vesztegetni való idônk - Rodenburg úr értékeli a gyors és minôségi munkát. Hol bujkál most Jacob van Berg?";
			link.l2.go = "Longway_neutral";
			link.l3 = "Nos, az enyém pedig Charles de Maure! Remélem, hogy a miénk jól fog mûködni együtt! Szóval, mynheer Longway, mondja meg, kérem, hol keressük Jacob van Berget?";
			link.l3.go = "Longway_enemy";
			NextDiag.TempNode = "First time";
			pchar.questTemp.HWIC.Holl.JacobCity = SelectJacobCity();
		break;
		
//-----------------------------------------------за Голландию-----------------------------------------------
		case "Longway_neutral":
			dialog.text = "Biztos vagyok benne, hogy jól fogunk együtt dolgozni, chuanzhang. Jacob van Berg jelenleg a "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Gen")+". Találkozót beszéltem meg vele a helyi kocsmában. Ott lesz.";
			link.l1 = "Induljunk!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayNeutral = "true";//признак враждебности китайца
		break;
		
		case "Longway_enemy":
			dialog.text = "A mynheer Rodenburg jogrendje Longway számára... Jacob van Berg jelenleg a "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Gen")+". Találkozót beszéltem meg vele a helyi kocsmában. Ott lesz.";
			link.l1 = "Induljunk!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayEnemy = "true";//признак враждебности китайца
			notification("Longway helyteleníti", "Longway");
		break;
		
		case "Longway_friend":
			dialog.text = "Longway mindent megtesz, amit tud, chuanzhang. És Jacob van Berg jelenleg a "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat")+". Megbeszéltem vele egy találkozót a helyi kocsmában. Ott lesz.";
			link.l1 = "Induljunk!";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayFriend = "true";//признак враждебности китайца
			notification("Longway jóváhagyja", "Longway");
		break;
		
		case "Longway_JacobGo":
			//Лонгвэя - в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;//полубессмертен
			npchar.loyality = 18;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", -1);
			AddQuestRecord("Holl_Gambit", "1-8");
			AddQuestUserData("Holl_Gambit", "sCity", XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat"));
			AddMapQuestMarkCity(pchar.questTemp.HWIC.Holl.JacobCity, true);
			AddLandQuestMark(characterFromId(""+pchar.questTemp.HWIC.Holl.JacobCity+"_tavernkeeper"), "questmarkmain");
			pchar.questTemp.HWIC.Holl = "JacobOnMain";
			if(bImCasual)
			{
				NewGameTip("Felfedezô mód: a küldetés idôtartama megduplázódott");
				SetFunctionTimerCondition("JacobOnMainOver", 0, 0, 30, false);
			}
			else SetFunctionTimerCondition("JacobOnMainOver", 0, 0, 15, false);
		break;
		
		case "hired":
			dialog.text = "Mit tehet Longway, chuanzhang?";
			link.l1 = "Egyelôre semmit.";
			link.l1.go = "exit";
			NextDiag.TempNode = "hired";
		break;
		
		case "MC_GoAway":
			PlaySound("Voice\English\hambit\Longway-02.wav");
			if (pchar.questTemp.HWIC.Holl == "MirageFail")
			{
				dialog.text = "Te idióta mongol bolond, chuanzhang! Könnyû dolgunk volt - elfogni 'Mirage' veszteség nélkül 'Meifeng'. Könnyû célpont volt a csuanzhangja nélkül, mégsem végezted el a feladatot\nLongway nem fog szolgálni téged, és nem is lát többé. Longway biztos benne, hogy Mynheer Rodenburg jóváhagyja a döntését.";
				link.l1 = "A pokolba veled és a mestereddel!";
				link.l1.go = "exit";
				AddQuestRecord("Holl_Gambit", "1-10");
			}
			if (pchar.questTemp.HWIC.Holl == "JacobOnMain" || pchar.questTemp.HWIC.Holl == "JacobInRoom")
			{
				dialog.text = "Te idióta mongol, chuanzhang! Túl sok idôt vesztegettünk a saját ügyeid megoldására ahelyett, hogy Jacob van Berggel találkoztunk volna. Ô már elment "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat")+"\nElbuktad a feladatot. Longway nem akar sem szolgálni téged, sem látni téged többé. Longway biztos benne, hogy Mynheer Rodenburg jóváhagyja a döntését.";
				link.l1 = "A pokolba veled és a mestereddel!";
				link.l1.go = "exit";
				AddQuestRecord("Holl_Gambit", "1-9");
			}
			if (pchar.questTemp.HWIC.Holl == "lateVillemstad")
			{
				dialog.text = "Chuanzhang, túl sok idôt pazaroltál el eredménytelenül. Ez nem a te hajód és Longway nem a te segéded. Longway visszatér Willemstadba\nLongway nem szolgál téged, és nem is látlak többé. Longway biztos benne, hogy Mynheer Rodenburg jóváhagyja a döntését.";
				link.l1 = "A pokolba veled és a mestereddel!";
				link.l1.go = "exit";
			}
			PChar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)//если сам на Мейфенг
			{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "Boat";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			}
			else
			{
				for(i=1; i < COMPANION_MAX; i++)
				{
					int iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Holl.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Detector = "holl_fail";
		break;
		
		case "Longway_hire":
			PlaySound("Voice\English\hambit\Longway-03.wav");
			dialog.text = "Chuanzhang, Longway elhagyta Mynheer Rodenburgot. Longway soha nem megy vissza hozzá. Kedves voltál Longwayhez, és bátor vagy, chuanzhang. Longway csatlakozni akar a legénységedhez, mint a szolgád, kapitány úr.";
			link.l1 = "Nem szolgaként, hanem tisztként! Üdvözöllek a fedélzeten, barátom!";
			link.l1.go = "Longway_hire_1";	
			link.l2 = "Nem, köszönöm, Longway. Szabad ember vagy. Nincs szükségem a szolgálataira.";
			link.l2.go = "Longway_exit";	
		break;
		
		case "Longway_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 30.0);
			AddQuestRecord("Holl_Gambit", "1-37");
		break;
		
		case "Longway_hire_1"://нанимаем китайца
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "HalfImmortal");
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.CanTakeMushket = true;
			npchar.Payment = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Longway_officer";
			npchar.quest.meeting = true;
			npchar.HoldEquip = true;
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 200, 200);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			AddQuestRecord("Holl_Gambit", "1-38");
			
			//Sinistra - квест Лонгвэя "Путеводная звезда"
			PChar.quest.PZ_Start.win_condition.l1 = "location";
			PChar.quest.PZ_Start.win_condition.l1.location = "Curacao";
			PChar.quest.PZ_Start.win_condition = "PZ_Start";
		break;
		
//---------------------------------------------против всех-------------------------------------------------
		case "Longway_abordage":
			PlaySound("Voice\English\hambit\Longway-02.wav");
			dialog.text = "Miért álltál meg? Megölni. Longway fáradt, Longway halált akar. Xing... bocsáss meg.";
			link.l1 = "Ne olyan gyorsan, kínai. Megöllek, ha akarlak, de elôbb beszélnem kell veled. A sorsod a jövôbeli tetteidtôl függ. Most pedig, üdvözöllek a raktérben!";
			link.l1.go = "Longway_abordage_1";			
		break;
		
		case "Longway_abordage_1":
			AddQuestRecord("Holl_Gambit", "3-45");
		    DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
            DialogExit();
			LAi_SetPlayerType(pchar);
			pchar.questTemp.HWIC.Self = "LongwayPrisoner";
			npchar.lifeday = 0;
			SetFunctionTimerCondition("RemoveLongwayOver", 0, 0, 1, false);//таймер до конца суток, ибо нефиг
		break;
		
		case "Longway_prisoner":
			DelLandQuestMark(npchar);
			dialog.text = "";
			link.l1 = "Most már beszélhetünk anélkül, hogy az acél csattanása zúgna a fülembe. Figyelj Longway, információra van szükségem, és nincs kétségem afelôl, hogy tudod, amit tudnom kell. A kérdés az, hogy a könnyebb vagy a nehezebb utat választod?";
			link.l1.go = "Longway_prisoner_1";			
		break;
		
		case "Longway_prisoner_1":
			dialog.text = "";
			link.l1 = "Hallgatni? Jól van. Ajánlok egy alkut. Megkímélem az életét, és a következô partra juttatom. Cserébe elmondod, hová és miért küldött téged Lucas Rodenburg. Áll az alku?";
			link.l1.go = "Longway_prisoner_2";			
		break;
		
		case "Longway_prisoner_2":
			dialog.text = "";
			link.l1 = "Tudom, hogy értesz angolul, hollandul és franciául. És jó hallgatóság is vagy. Itt az ideje, hogy elkezdjünk beszélni. Végül mindent el fogsz mondani, amit tudsz. Tudom, hogy ti kínaiak büszkék vagytok a kínzás mûvészetére, de mi, nyugati emberek is fejlôdtünk ebben az ôsi tudományban. Alonso mestere az emberek nyelvének eloldásának. A Szent Inkvizíció kihallgatója volt Santiagóban, mielôtt a hajómra szerzôdött. Mindenféle trükköt ismer, amit a szent atyáktól tanult, akik tökéletesítették a nép vallomásra bírásának mûvészetét... még csak protestánsnak sem kell lenni!";
			link.l1.go = "Longway_prisoner_3";			
		break;
		
		case "Longway_prisoner_3":
			dialog.text = "";
			link.l1 = "A szellemességemet elpazaroltam rád. Mindent el fogsz mondani nekem, ferdeszemû barátom... Mindent... De nem fogsz sokáig élni utána, nem, nem fogsz. A tested sokat fog szenvedni az Alonsóval való találkozás után/. Szóval a döntés a tiéd. Vagy elmondod az igazat és életben maradsz, vagy elmondod az igazat és kínok között halsz meg a kínpadon. Fájdalommal teli kínpadon. Érted? Ne aggódj, gondoskodom róla, hogy egy pap jelen legyen, aki kereszténynek keresztel, hogy megkíméljem pogány lelkedet a pokol örök tüzétôl.";
			link.l1.go = "Longway_prisoner_4";
		break;
		
		case "Longway_prisoner_4":
			dialog.text = "";
			link.l1 = "Látom, hogy a fekete szemedben egyre nô a kétely. Miért kellene meghalnod a gazdád bûneiért? Megéri ô ezt? Rodenburg tényleg megéri, hogy a lelkedet kitépjék szenvedô testedbôl?";
			link.l1.go = "Longway_prisoner_5";			
		break;
		
		case "Longway_prisoner_5":
			dialog.text = "Hosszú beszéd. De elôször is, Longway biztos akar lenni benne, hogy tartod a szavad, chuanzhang.";
			link.l1 = "Ha! Bölcs szavak! A szavamat adom, fiú.";
			link.l1.go = "Longway_prisoner_6";			
		break;
		
		case "Longway_prisoner_6":
			dialog.text = "Sajnálom chuanzhang, a szavad nem elég. Szerezz információt, és utána öld meg Longwayt! Longway garanciát akar.";
			link.l1 = "Úgy alkudozol, mint egy zsidó. Milyen garanciákat akarsz?";
			link.l1.go = "Longway_prisoner_7";			
		break;
		
		case "Longway_prisoner_7":
			dialog.text = "Van egy kis Marie Galante sziget Guadeloupe déli részén. Cape Inaccessible. Szállj le ott Longway-vel és add neki a fegyvert. Csak akkor mondja el mindent, amit Lucas Rodenburgról tud.";
			link.l1 = "Nem vagy abban a helyzetben, hogy alkudozz velem, kínai.";
			link.l1.go = "Longway_prisoner_8";			
		break;
		
		case "Longway_prisoner_8":
			dialog.text = "Te is ezt tennéd Longway helyében, chuanzhang. Nem lesz könnyû az emberednek szavakat kicsikarni belôlem, még kínzásokkal sem. Longway nem gyenge fehér ember.";
			link.l1 = "Rendben. Rendben. De figyelmeztetlek - ne próbálj meg kijátszani, vagy személyesen váglak darabokra. Ezerszer, és lassan... ahogy a császáraid teszik. Alonso!";
			link.l1.go = "Longway_prisoner_9";
			// belamour legendary edition -->
			link.l2 = "Igazat beszélsz. De ne feledd - túl messzire jutottam ahhoz, hogy ezt elszúrd. Ha megpróbálsz megállítani, véget vetek az életednek, mintha egy rovarra lépnél.";
			link.l2.go = "Longway_prisoner_9a";
		break;
		
		case "Longway_prisoner_9a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			DialogExit();
			NextDiag.Currentnode = "Longway_prisoner_0";
			npchar.greeting = "longway";
			sld = characterFromId("Sailor_3");
			sld.dialog.currentnode = "Sailor_deck_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
			pchar.quest.RemoveLongwayOver.over = "yes";//снять таймер
			pchar.quest.RemoveLongwayTimer.win_condition.l1 = "Timer";
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.function = "RemoveLongwayOver";
			pchar.questTemp.HWIC.Self = "GotoGuadeloupe";
		break;
		
		case "Longway_prisoner_9":
			ChangeCharacterComplexReputation(pchar, "nobility",-5);
			AddCharacterExpToSkill(pchar, "FencingL", 30);
			AddCharacterExpToSkill(pchar, "FencingS", 30);
			AddCharacterExpToSkill(pchar, "FencingH", 30);
			AddCharacterExpToSkill(pchar, "Pistol", 30);
			// <-- legendary edition
			DialogExit();
			NextDiag.Currentnode = "Longway_prisoner_0";
			npchar.greeting = "longway";
			sld = characterFromId("Sailor_3");
			sld.dialog.currentnode = "Sailor_deck_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
			pchar.quest.RemoveLongwayOver.over = "yes";//снять таймер
			pchar.quest.RemoveLongwayTimer.win_condition.l1 = "Timer";
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.function = "RemoveLongwayOver";
			pchar.questTemp.HWIC.Self = "GotoGuadeloupe";
		break;
		
		case "Longway_prisoner_0":
			dialog.text = "Megérkeztünk Marie Galantéra, chuanzhang?";
			link.l1 = "Nyugodj meg, hamarosan ott leszünk.";
			link.l1.go = "exit";
			NextDiag.Tempnode = "Longway_prisoner_0";
		break;
		
		case "Longway_prisoner_10":
			dialog.text = "Megtartottad a szavad, chuanzhang. Ahogy Hosszúút is. Tudni akartál Longway küldetésérôl?";
			link.l1 = "Igen. De engedd meg, hogy emlékeztesselek a saját ígéretedre: elmondasz nekem *mindent*, amit tudsz.";
			link.l1.go = "Longway_prisoner_11";			
		break;
		
		case "Longway_prisoner_11":
			dialog.text = "Longway emlékszik. Mindenre válaszol, amit Rodenburgról kérdezel, chuanzhang.";
			link.l1 = "Kezdj el beszélni.";
			link.l1.go = "Longway_prisoner_12";			
		break;
		
		case "Longway_prisoner_12":
			dialog.text = "'Meifeng' Willemstad kikötôjébôl hajózott észak felé, Szent Kristóf partjai felé. Öt nap múlva érkezne egy gálya Peter Stuyvesant parancsnoksága alatt. Longway parancsa az volt, hogy elsüllyessze ezt a hajót a kapitánnyal a fedélzetén.";
			link.l1 = "Isten az égben! Rodenburg utasította, hogy ölje meg Stuyvesantot? Ez ôrültség!";
			link.l1.go = "Longway_prisoner_13";			
		break;
		
		case "Longway_prisoner_13":
			dialog.text = "Longway igazat beszél, kapitány. Ez Mynheer Rodenburg parancsa volt. Longwaynek nem tetszett, de Longway nem kérdôjelezi meg a parancsokat.";
			link.l1 = "Mennyire hasonlít egy kínaira. Milyen játékot ûz a gazdád?";
			link.l1.go = "Longway_prisoner_14";			
		break;
		
		case "Longway_prisoner_14":
			dialog.text = "Már nem a mesterem, chuanzhang. Már régóta nem fogok visszatérni Mynheer Rodenburgba. Rodenburg átvette a hatalmat Curacaón. Mathias Beck könnyû préda volt, Rodenburg tekintélye és a parancsnokkal való kapcsolatai elégségesek ahhoz, hogy a kormányzót börtönbe juttassa\nAz egyetlen akadály, ami maradt, a Nyugat-indiai Társaság igazgatója, Mynheer Stuyvesant. Miután Stuyvesantot likvidálták, Rodenburg a holland gyarmatokon minden hatalmi tisztséget megkaparint.";
			link.l1 = "Mondja, Longway, mi késztetett egy olyan tekintélyes és befolyásos embert, mint Rodenburg, arra, hogy ilyen radikális lépéseket tegyen a társasága és a köztársasága ellen? És ne mondja nekem, hogy a nap érintése vagy az ôrület kitörése miatt.";
			link.l1.go = "Longway_prisoner_15";			
		break;
		
		case "Longway_prisoner_15":
			dialog.text = "Longway meg akarta ismerni magát tôled, chuanzhang. Te voltál az, aki elfoglaltad a Társaság csomaghajóját, és levelet vittél Rodenburgba, igaz? Az ok, ami a levélben állt.";
			link.l1 = "Most már értem... Úgy látszik, John Murdock archívumában sok csodálatos dolog van, ami Rodenburgot eléggé megrémítette ahhoz, hogy lázadást indítson a saját országa ellen.";
			link.l1.go = "Longway_prisoner_16";			
		break;
		
		case "Longway_prisoner_16":
			dialog.text = "Akarsz még valamit tudni, chuanzhang?";
			link.l1 = "Igen, uram. Mit tett még Rodenburg?";
			link.l1.go = "Longway_prisoner_17";			
		break;
		
		case "Longway_prisoner_17":
			dialog.text = "Mynheer Rodenburg megparancsolta, hogy öljenek meg téged. Longway Caracasban járt, mielôtt Stuyvesantra vadászott, és találkozott Chuanzhang Jacobbal, és parancsot adott neki.";
			link.l1 = "Jacob van Berg kapitány?";
			link.l1.go = "Longway_prisoner_18";			
		break;
		
		case "Longway_prisoner_18":
			dialog.text = "Jól informáltak. Igen, uram. Chuanzhang Jacob van Berg vadászik önre, kapitány. Elôbb-utóbb megtalálja magát. Senki sem tud sokáig elbújni van Berg elôl.";
			link.l1 = "Ha vérzik, meg tudom ölni. Elintézem van Berget és a szellemhajóját.";
			link.l1.go = "Longway_prisoner_19";			
		break;
		
		case "Longway_prisoner_19":
			dialog.text = "Sokat tudsz, chuanzhang. Longwaynek nincs mit hozzátennie. Kérdezd meg, ha még mindig van valami kérdeznivalód.";
			link.l1 = "Stuyvesant a Szent Kristóf partjainak közelében lesz?";
			link.l1.go = "Longway_prisoner_20";			
		break;
		
		case "Longway_prisoner_20":
			dialog.text = "Igen, chuanzhang. Egy hét múlva megtalálod a gályáját a sziget partjainál.";
			link.l1 = "Szép volt! Kapjuk el ezt a rókát a saját csapdájában... Nincs több kérdésem. Mindent tudok, amit tudni akartam.";
			link.l1.go = "Longway_prisoner_21";			
		break;
		
		case "Longway_prisoner_21":
			dialog.text = "Egy utolsó tanács, chuanzhang. El kell venned 'Meifeng' , ha közel akarsz kerülni a gályához anélkül, hogy megtámadnának.";
			link.l1 = "Értettem. Köszönöm az információt.";
			link.l1.go = "Longway_prisoner_22";			
		break;
		
		case "Longway_prisoner_22":
			dialog.text = "Longway most indul. Viszlát, chuanzhang.";
			link.l1 = "Isten veled, keleti barátom.";
			link.l1.go = "Longway_prisoner_23";			
		break;
		
		case "Longway_prisoner_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "ReturnShoreToNormal", -1);
			npchar.lifeday = 0;
			AddQuestRecord("Holl_Gambit", "3-49");
			pchar.questTemp.HWIC.Self = "MeetingStivesant";
			pchar.quest.Seek_Piter.win_condition.l1 = "location";
			pchar.quest.Seek_Piter.win_condition.l1.location = "Nevis";
			pchar.quest.Seek_Piter.function = "CreatePiterHalleon";
			pchar.quest.RemoveLongwayTimer.over = "yes";//снять прерывание
			SetFunctionTimerCondition("QuestShipsTerms_Over", 0, 0, 8, false); // таймер
			AddMapQuestMarkIsland("Nevis", true);
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Longway_officer":
			dialog.text = "Hosszú utat hallgass, chuanzhang.";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Longway, egy ôsi indiai városba, Tayasalba megyek. Tisztázzuk, ez egy nagyon veszélyes utazás lesz, és egyben misztikus is - a teleport bálványon keresztül jutunk oda. Csatlakozol hozzám?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Longway, adj egy teljes hajójelentést.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Azt akarom, hogy minden alkalommal, amikor kikötünk, vásároljon bizonyos árukat.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Az Ön utasítására érkeztem, kapitány.";
				Link.l2 = "Több parancsot kell adnom neked.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "Longway_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Hallgassa meg a parancsomat!";
            Link.l1.go = "stay_follow";
			link.l2 = "Semmi. Lelépni!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Longway_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Longway még sosem volt purser, chuanzhang. Longway meg tudja mondani, hogyan navigálj Trinidadból Havannába, és mennyi idô alatt érsz oda. De Longway soha nem számolja a rakományt, az eladásokat és a kereskedelmet.";
			Link.l1 = "Azt hiszem, igazad van. Kár lenne elpazarolni egy ilyen jó navigátort.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "A Longway nem kereskedik a gwailo-val, chuanzhang. A Longway mindig a kormánynál állt, nem a boltban, ahol az öreg horgasorrú alkudozik az utolsó darab pesóra.";
			link.l1 = "Hm, igazad van. Valószínûleg megijesztenéd a kereskedôket.";
			link.l1.go = "exit";
		break;

		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Hallgatlak.";
			Link.l1 = "Beszéljünk a beszállásról.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Beszéljünk a hajódról.";
			Link.l2.go = "Companion_TaskChange";
			if (bBettaTestMode) // Только при бета-тесте
			{
				Link.l3 = "Azt akarom, hogy egy idôre hagyja el a századomat, és keresse a szerencséjét egyedül.";
				Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "Eddig semmi.";
			Link.l8.go = "exit";
		break;

		case "Companion_TaskBoarding":
			dialog.Text = "Mi a kívánságod.";
			Link.l1 = "Ne szállj fel az ellenséges hajókra. Vigyázz magadra és a legénységre.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Azt akarom, hogy agresszívan szálljatok fel az ellenséges hajókra.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "Mi a kívánságod.";
			Link.l1 = "Ne cseréld el a hajódat egy másikra, miután felszálltál rá. Túl értékes.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Amikor ellenséges hajókra szállsz fel, elviheted ôket magadnak, ha történetesen tisztességesek.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Igenis, uram.";
			Link.l1 = "Pihenj.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "Úgy lesz.";
			Link.l1 = "Pihenj.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;

		case "Companion_TaskChangeNo":
			dialog.Text = "Igenis, uram.";
			Link.l1 = "Úgy lesz.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = "Úgy lesz.";
			Link.l1 = "Pihenj.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========////////////////////////////////////////
		case "stay_follow":
            dialog.Text = "Parancsok, chuanzhang?";
            Link.l1 = "Álljatok meg!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Kövessetek és tartsátok a lépést!";
            Link.l2.go = "Boal_Follow";
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Változtassátok meg a lôszer típusát a lôfegyvereitekhez.";
					Link.l3.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Változtasd meg a muskétád lôszertípusát.";
					Link.l4.go = "SetMusketBullets";
				}
					Link.l5 = "Változtasd meg a harcban használt elsôdleges fegyveredet.";
					Link.l5.go = "SetPriorityMode";
					Link.l6 = "Azt akarom, hogy meghatározott távolságból tüzelj az ellenségre, Lonway.";
					Link.l6.go = "TargetDistance";
			}	
		break;
		
		case "SetGunBullets":
			Dialog.Text = "A lôszer típusának kiválasztása:";
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

		case "SetMusketBullets":
			Dialog.Text = "Válaszd kia lôszertípust:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "A harc elején használni fogod:";
			Link.l1 = "Penge";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Muskéta";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Változott a helyzet!";
            Link.l1 = "Elmehetnek.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Változott a helyzet!";
            Link.l1 = "Elmehetnek.";
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "És milyen távolság lenne az? Ne feledd, kapitány úr, húsz méteren túl nem tudsz eltalálni semmit muskétával.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Hogy érti ezt, kapitány úr?";
				link.l1 = "Bocsánat, néha elfelejtem, hogy nem értesz a viccekhez.";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Tartom a pozíciómat, de tüzelek minden ellenségre, aki túl közel jön. Ezt akarja?";
				link.l1 = "Igen, pontosan, Lonway.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Ez túl messzire megy, kapitány úr. Talán a tömegbe beletalálsz, de egyetlen célpontra célozni - semmi esély.";
				link.l1 = "Egy próbát megérne, de rendben.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Értem, kapitány úr.";
			link.l1 = "Kiváló.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Longway már régóta követ téged. Longway követni fog téged, mint mindig. Longway nem hagyja el a chuanzhangját.";
			link.l1 = "Köszönöm, Longway! Örülök, hogy igazam volt veled kapcsolatban.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Mikor kezdünk?";
			link.l1 = "Kicsit késôbb. Fel kell készülnünk rá.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "24");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string SelectJacobCity()
{
	string sTemp;
	switch (hrand(4))
	{
		case 0: sTemp = "Cumana" break;
		case 1: sTemp = "Caracas" break;
		case 2: sTemp = "Maracaibo" break;
		case 3: sTemp = "Cartahena" break;
		case 4: sTemp = "Portobello" break;
	}
	return sTemp;
}
