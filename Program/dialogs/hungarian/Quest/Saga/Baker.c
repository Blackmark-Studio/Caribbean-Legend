// Раймонд Бейкер - палач Сент-Джонса и возможный офицер
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
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Kérsz valamit?";
			link.l1 = "Nem, semmi.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "baker":
			dialog.text = "Köszönöm, kapitány! El sem tudom képzelni, mit tettem volna nélküled...";
			link.l1 = "El tudom képzelni. Éhen haltál volna, vagy egy dominikai vadember gyomrában végezted volna. De most van esélyed, hogy megháláld nekem.";
			link.l1.go = "baker_1";
		break;
		
		case "baker_1":
			dialog.text = "Miben segíthetek, kapitány?";
			link.l1 = "Egy emberrôl szeretnék többet tudni. Ô a közös barátunk, hogy úgy mondjam. Valójában egy nagyon közeli barátja. Úgy értem, Butcher kapitány. Igen, akit húsz évvel ezelôtt felakasztott. Uram, miért vagy ilyen sápadt? Kérsz egy korty rumot?";
			link.l1.go = "baker_2";
		break;
		
		case "baker_2":
			dialog.text = "Ô küldte magát?";
			link.l1 = "Badarság! Hogyan lehetnék 'küldve tôle' , ha meghalt! Engem inkább érdekelnek a hátrahagyott dolgai, mint maga Mészáros. Levelek, dokumentumok, ilyesmik. Talán talált valamit a zsebében... Várjon! Nem értem. Tényleg azt hiszi, hogy Mészáros életben van? Te magad végezted ki!";
			link.l1.go = "baker_3";
		break;
		
		case "baker_3":
			dialog.text = "Bassza meg! Fogalmad sincs. Ez azt jelenti, hogy nem Mészáros küldött téged, ahogy gondoltam...";
			link.l1 = "Nocsak, nocsak. Ez egyre érdekesebb lesz. Úgy tûnik, Henrynek minden oka megvolt rá, hogy féljen a Mészárostól, és ezért halt meg a szívrohamban... Butcher életben van?";
			link.l1.go = "baker_4";
		break;
		
		case "baker_4":
			dialog.text = "Igen, kapitány... És engem keresnek.";
			link.l1 = "Raymond, azt mondták nekem, hogy nem vagy hülye ember. Ne próbálj meg játszadozni velem. Itt nem fenyegeti semmi veszély. Mondjon el mindent, amit tud, és én kitalálok valamit, amivel segíthetek. Talán közös ellenségeink vannak. Kezdjük a Mészárossal.";
			link.l1.go = "baker_5";
		break;
		
		case "baker_5":
			dialog.text = "Életben van, de a neve már más! Az emberei meglátogattak a kivégzés éjszakáján. Jackman és egy másik férfi, valami furcsa becenévvel. Amennyire emlékszem, a 'Fuldokló'.volt az.";
			link.l1 = "Hóhér. Henry, a hóhér.";
			link.l1.go = "baker_6";
		break;
		
		case "baker_6":
			dialog.text = "Így van! Egyszerû ajánlatot tettek nekem: vagy meghalok a legfájdalmasabb módon, vagy megmentem a kapitányukat. Így hát meg kellett színlelnem a kivégzést egy különleges felszereléssel, amit a szabadidômben készítettem. Látod, egy ilyen övekbôl és bilincsekbôl álló szerkezet képes elosztani a test súlyát.\nMindössze annyit kellett tennem, hogy összekötöm egy titkos kampóval a hurokban. A 'corpse' azonban jól kellett játszania a szerepét. Azt kell mondjam, hogy Lawrence színészi játéka volt a leghihetôbb, mindent jól csinált, kivéve, hogy nem volt hajlandó bepisilni, mert....";
			link.l1 = "Hívtad a Mészárost 'Lawrence-t?'?";
			link.l1.go = "baker_7";
		break;
		
		case "baker_7":
			dialog.text = "Ez az igazi neve. Mondtam, hogy Lawrence Beltrope-nak hívják. Nyugtalan vagyok, mióta egy évvel ezelôtt visszatért a Karib-tengerre. És amikor megtudtam, hogy néhány rossz ember keres engem...\nMég egy vallomást is írtam a hatóságoknak, biztos, ami biztos. Mindig magamnál tartom, mert túlságosan félek, hogy kiadjam. Még azt gondolnák, hogy készséges felbujtó voltam. Kérem, engedje meg, hogy a legénységével maradjak. Esküszöm, kiváló orvos vagyok, és sokat tudok segíteni.";
			link.l1 = "Rendben. És mi lesz Butcher... eh, Beltrope személyes tárgyaival? Rokona Thomas Beltrope-nak?";
			link.l1.go = "baker_8";
		break;
		
		case "baker_8":
			dialog.text = "Fogalmam sincs. Nem maradt semmi különleges magától Beltrope-tól. De odaadok mindent, amim van, és azt csinálsz vele, amit akarsz. A táskámban van minden, a témával kapcsolatos irat. Mindent félretettem a biztonság kedvéért, és közel tartom magamhoz.\nTessék, nézze meg... ez Mészáros kapitány legendája, ez az én vallomásom... Ezek a dolgok Joshua Leadbeateré voltak...";
			link.l1 = "Hagyd abba! Leadbeater? Ki az?";
			link.l1.go = "baker_9";
		break;
		
		case "baker_9":
			dialog.text = "Ó! Ô egy nagyon különleges ember volt. Ô volt az, aki maga üldözte Mészárost. Az emberek úgy emlékeztek rá, mint a 'maszkos emberre'. Nem sokkal Mészáros kivégzése után meggyilkolták. Valaki egy cápafoggal vágta el a torkát! Egy vágás és vége volt. Amikor még élt, nagyon sokat szenvedhetett.\nHa láttad volna az arcát a maszk alatt, nem volt más, csak hús! Ez a napló lap volt a zsebében, amikor meghalt. Jessica Rose írásaiból származhatott. Hátborzongató történet! Olvassátok el, sokkal érthetôbbé teszi a dolgokat.\nEz pedig maga a fog. Látod a betûket? S.D.... Bármit is jelentsen ez. Néhány vérfolt is maradt rajta.";
			link.l1 = "Elég volt! Mindent alaposan el kell olvasnom, és át kell gondolnom. És te leszel az utasom vagy a hajóorvosom, amíg ezt az egészet elintézem. Szabadon lélegezhet, Raymond, biztonságban van a hajómon.";
			link.l1.go = "baker_10";
		break;
		
		case "baker_10":
			DialogExit();
			sld = characterFromId("Baker_Cap");
			LAi_SetImmortal(sld, false);
			sld.lifeday = 0;
			//sld.ship.hp = 0;
			//sld.SinkTenPercent = true;
			bQuestDisableMapEnter = false;
			GiveItem2Character(pchar, "shark_teeth");
			GiveItem2Character(pchar, "letter_jess");
			GiveItem2Character(pchar, "letter_baker"); // показания бейкера
			ChangeItemDescribe("letter_baker", "itmdescr_letter_baker"); // Addon-2016 Jason
			AddQuestRecordInfo("Legend_CapBucher", "1");
			AddQuestRecordInfo("Letter_jess", "1");
			AddQuestRecord("Shadows", "5");
			pchar.questTemp.Saga.Shadows = "islatesoro";
			// в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.CompanionDisable = true; //нельзя в компаньоны
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			NextDiag.CurrentNode = "Baker_officer";
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			AddCharacterExpToSkill(pchar, "Sailing", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Baker_officer":
			dialog.text = "Igen, kapitány?";
			Link.l1 = "Hallgassa meg a parancsomat!";
            Link.l1.go = "stay_follow";
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Raymond, adjon teljes jelentést a hajóról.";
			    Link.l11.go = "QMASTER_1";

			    // Warship. Автозакупка товара
				Link.l12 = "Azt akarom, hogy minden alkalommal, amikor kikötünk, vásároljon bizonyos árukat.";
				Link.l12.go = "QMASTER_2";
			}
			
			link.l2 = "Semmiség. Lelépni!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Baker_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
        case "QMASTER_1":
			dialog.Text = "Ugyan már, kapitány, én orvos vagyok, nem pénztáros. Bár régebben más minôségben dolgoztam... nem számít. Nem igazán értek a könyveléshez, sajnálom.";
			Link.l1 = "Rendben, legyen. Maga az orvosom - ahogy abban megegyeztünk, miután csatlakozott a legénységemhez.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Kapitány, hogy teljesen ôszinte legyek, nem sok tapasztalatot szereztem a kereskedelemben. Soha nem alkudoztam, soha nem követtem az árcédulákat. És... Inkább maradnék a hajón, ha nem bánja. Néhány kereskedô talán felismer engem, és mire észbe kapna, máris jönnek a maszkosok.";
			link.l1 = "Szóval, továbbra is a múltadtól való félelemben fogsz élni... Rendben, lélegezz ki, majd én magam megteszem.";
			Link.l1.go = "exit";
        break;
		
		case "stay_follow":
            dialog.Text = "Rendelések?";
            Link.l1 = "Álljatok ide!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Kövessetek és tartsátok a lépést!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Változtasd meg a lôszer típusát a fegyveredhez.";
					Link.l3.go = "SetGunBullets";
				}	
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
	//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
