// Эркюль Тонзаг, он же Плешивый Гастон
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
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MainBegin")
			{
				dialog.text = "Nos, hello, " + pchar.name + ". Örülök, hogy életben vagy.";
				link.l1 = "Gaston! Te vagy az?";
				link.l1.go = "SJ_talk";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetTonzag")
			{
				dialog.text = "Üdvözlet, " + pchar.name + ". Már tudok az ügyleteidrôl - John mindent elmondott. Nem is tudom, mit mondjak. Csodállak téged!";
				link.l1 = "Örülök, hogy ilyen dicséretet hallok tôled, Hercule!";
				link.l1.go = "SJ_talk_11";
				break;
			}
			dialog.text = "Jó napot kívánok. Van valami dolga számomra?";
			link.l1 = "Nem. Az én hibám. Sajnálom, uram. Viszontlátásra. .";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "SJ_talk":
			dialog.text = "Ezen a néven ismertél meg. De az igazi nevem Hercule. Hercule Tonzag.";
			link.l1 = "Szent Isten! Én is örülök, hogy látlak... Nem ismertelek meg a harc hevében. Épp idôben jöttél a segítségeddel.";
			link.l1.go = "SJ_talk_1";
		break;
		
		case "SJ_talk_1":
			dialog.text = "Közvetlenül a távozása után kaptam a hírt, hogy Fleetwood fokozta a háza védelmét. Felvetettem, hogy talán csapda állhat a háttérben. Azonnal Antigua felé vettem az irányt a hajómon 'Twilight' - és, mint most már látod, jó okom volt rá.";
			link.l1 = "Ez igaz. Alig bírtam elintézni az ôröket a házban, de túlságosan kimerült voltam ahhoz, hogy az utcán folytassam a harcot...";
			link.l1.go = "SJ_talk_2";
		break;
		
		case "SJ_talk_2":
			dialog.text = "A harc után Fleetwood körözési listára tett egy holland kémet. Azt hitték, hogy maga holland kém. Megrögzött ellenségeskedésben van velük. A legrosszabb az volt, hogy egy katona a házban túlélte, és emlékezett az arcodra. De mindegy is, most már nem probléma. Befejeztem, amit elkezdtél. Ez a katona többé nem fog tudni felismerni senkit, és senki sem fogja felismerni...";
			link.l1 = "Te ölted meg? Értem...";
			link.l1.go = "SJ_talk_3";
		break;
		
		case "SJ_talk_3":
			dialog.text = "Igen. Amíg te eszméletlenül feküdtél John házában, én megsebesítettem Fleetwoodot, de a rohadéknak sikerült túlélnie. Megvakítottam - dobtam borsot a szemébe, aztán leütöttem, mielôtt esélye lett volna kardot rántani. De a szemétláda hauberkát viselt az egyenruhája alatt - ez mentette meg az életét. Okos. Most otthon marad az ágyban, fokozott biztonságban. Nagyon sajnálatos, hogy túlélte.";
			link.l1 = "Tehát a fô feladata Antiguán Fleetwood likvidálása volt?";
			link.l1.go = "SJ_talk_4";
		break;
		
		case "SJ_talk_4":
			dialog.text = "Általában igen. Most azonban lehetetlennek tûnik - a ház mindig be van zárva, féltucatnyi kézzel kiválasztott gárdista teljesít szolgálatot éjjel-nappal, és csak a bizalmasának engedik, hogy láthassa - egy öreg kánonôrnek, Charlie-nak, becenevén Knippelnek.";
			link.l1 = "Ez már valami...";
			link.l1.go = "SJ_talk_5";
		break;
		
		case "SJ_talk_5":
			dialog.text = "Várj egy kicsit... Bele akarsz avatkozni ebbe az ügybe?";
			link.l1 = "Miért ne? Nincs szüksége segítségre? Megmentettél, és én segíteni akarok. És még mindig szükségem van pénzre.";
			link.l1.go = "SJ_talk_6";
			// belamour legendary edition -->
			link.l2 = "Miért ne? Ti komoly emberek vagytok. És a komoly emberek nagylelkûen fizetnek. Én csak munkát keresek.";
			link.l2.go = "SJ_talk_6a";
		break;
		
		case "SJ_talk_6a":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 120);
			dialog.text = "Higgye el, barátom, ez nem fog sikerülni. Remek fickó vagy, igazi tehetség, és a napló, amit elhoztál, segített megtervezni a Fleetwood elleni merényletet, jól szeletelted az ôröket - de most már soha nem fogsz tudni Fleetwoodhoz jutni. Még nekem sincs a leghalványabb fogalmam sem arról, hogyan kell ezt megtenni.";
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				link.l1 = "Majd átgondolom a dolgot. Még van idôm. Kár, hogy a hajómat letartóztatták, és nincs legénységem.";
				link.l1.go = "SJ_talk_7";
			}
			else
			{
				link.l1 = "Majd átgondolom. Van idôm és hajóm.";
				link.l1.go = "SJ_talk_8";
			}
		break;
		
		case "SJ_talk_6":
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			dialog.text = "Higgye el, barátom, ez nem fog sikerülni. Remek fickó vagy, igazi tehetség, és a napló, amit elhoztál, segített megtervezni a Fleetwood elleni merényletet, jól szeletelted az ôröket - de most már soha nem fogsz tudni Fleetwoodhoz jutni. Még nekem sincs a leghalványabb fogalmam sem arról, hogyan kell ezt megtenni.";
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				link.l1 = "Majd átgondolom a dolgot. Még van idôm. Kár, hogy a hajómat letartóztatták, és nincs legénységem.";
				link.l1.go = "SJ_talk_7";
			}
			else
			{
				link.l1 = "Majd átgondolom. Van idôm és hajóm.";
				link.l1.go = "SJ_talk_8";
			}
		break;
		
		case "SJ_talk_7":
			dialog.text = "Ne aggódj emiatt. Amikor az öreg kádat letartóztatták, az összes tisztjét és néhány matrózt a 'Twilight'. fedélzetére vittem, ôk tudják, hogy életben van, és beleegyeztek, hogy szolgálatban marad. A naplóért cserébe pedig átadom a hajómat 'Twilight' önnek.";
			link.l1 = "Köszönöm! Ezt nem fogom elfelejteni!";
			link.l1.go = "SJ_talk_9";
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 46)
			{
				pchar.Ship.Type = GenerateShipHand(pchar, SHIP_CAREERLUGGER, 12, 580, 30, 800, 20000, 16.5, 65.5, 1.6);
			}
			else
			{
				pchar.Ship.Type = GenerateShipHand(pchar, SHIP_SCHOONER, 16, 1900, 50, 1350, 25000, 13.5, 55.0, 1.10);
			}
			pchar.Ship.name = "Twilight";
			SetBaseShipData(pchar);
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 46) pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
			else pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
			SetCrewQuantityFull(pchar);
			pchar.Ship.Crew.Morale = 80;
			pchar.Ship.Crew.Exp.Sailors = 90;
			pchar.Ship.Crew.Exp.Cannoners = 70;
			pchar.Ship.Crew.Exp.Soldiers = 70;
			SetCharacterGoods(pchar, GOOD_BALLS, 100);
			SetCharacterGoods(pchar, GOOD_GRAPES, 100);
			SetCharacterGoods(pchar, GOOD_KNIPPELS, 100);
			SetCharacterGoods(pchar, GOOD_BOMBS, 100);
			SetCharacterGoods(pchar, GOOD_FOOD, 100);
			SetCharacterGoods(pchar, GOOD_POWDER, 300);
			SetCharacterGoods(pchar, GOOD_WEAPON, 60);
			SetCharacterGoods(pchar, GOOD_MEDICAMENT, 60);
		break;
		
		case "SJ_talk_8":
			AddMoneyToCharacter(pchar, 15000);
			dialog.text = "Igen, szeretnék fizetni a naplóért. 15000 pezó - jelenleg sajnos nincs több pénzem. Majd egy nap alatt rendezzük a dolgot. ";
			link.l1 = "Nem szükséges. Ennyi elég lesz. Ha nem érkezett volna meg idôben, amúgy sem lett volna szükségem pénzre.";
			link.l1.go = "SJ_talk_9";
		break;
		
		case "SJ_talk_9":
			dialog.text = "Rendben, " + pchar.name + ", mennem kell. Még nem megyek vissza Bridgetownba. Ha valaha is szükséged lesz rám - kérdezd Johnt. Sok szerencsét!";
			link.l1 = "Sok szerencsét, Hercule!";
			link.l1.go = "SJ_talk_10";
		break;
		
		case "SJ_talk_10":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-13");
			pchar.questTemp.HWIC.Self = "HuntFleetwood";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "SJ_talk_11":
			dialog.text = "Szeretném átadni ezt a páncélt Fleetwood kiiktatására. Ez megvédi majd a jövôbeni csatákban. Most menjünk Johnhoz. Beszélni akar veled, és felajánl egy... érdekes ügyet.";
			link.l1 = "Köszönöm az ajándékot. Rendben, menjünk...";
			link.l1.go = "SJ_talk_12";
		break;
		
		case "SJ_talk_12":
			DialogExit();
			GiveItem2Character(pchar, "cirass7");//дать вещь
			sld = characterFromId("Merdok");
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetOwnerType(sld);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			AddQuestRecord("Holl_Gambit", "3-35");
		break;
		
		case "Tonzag_hired":
			dialog.text = "Én is szeretnék beszélni önnel, kapitány. Úgy volt, hogy megtanítalak a mesterségemre, de most már látom, hogy nekem kellene tanulnom tôled. Vegyen fel tisztnek a hajójára - nem fogja megbánni.";
			link.l1 = "Örömmel, Hercule! Üdvözlöm a legénységben!";
			link.l1.go = "Tonzag_hired_1";
			link.l2 = "Hercule, nem tudom elképzelni magam a felettesednek. Köszönöm az ajánlatát, de nem tudom elképzelni magát a beosztottamként.";
			link.l2.go = "Tonzag_exit";
		break;
		
		case "Tonzag_hired_1"://Тонзага - в офицеры
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetOfficerType(npchar);
			npchar.greeting = "tonzag_hire";
			NextDiag.CurrentNode = "tonzag_officer";
			npchar.quest.meeting = true;
			npchar.HoldEquip = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			LAi_SetImmortal(npchar, false);
			SetCharacterPerk(npchar, "ShipEscape");
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
		break;
		
		case "Tonzag_exit":
			dialog.text = "Ahogy kívánja, " + pchar.name + ". Viszlát! Talán még találkozunk. Öröm volt önnel dolgozni.";
			link.l1 = "Sok szerencsét, barátom!";
			link.l1.go = "Tonzag_exit_1";
		break;
		
		case "Tonzag_exit_1":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DialogExit();
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "tonzag_officer":
			dialog.text = "Hallgatlak, kapitány. Mit akar mondani?";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Hercule, a régi indiai Tayasal városába megyek, és ami még szokatlanabb, az utam egy teleportáló szobron keresztül vezet. Csatlakozik hozzám?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Hercule, adjon teljes jelentést a hajóról.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Azt akarom, hogy minden alkalommal, amikor kikötünk, vásároljon bizonyos árukat.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Az Ön utasítására érkeztem, kapitány.";
				Link.l2 = "Több parancsot kell kiadnom önnek.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "tonzag_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Hallgassa meg a parancsomat!";
            Link.l1.go = "stay_follow";
			link.l2 = "Egyelôre semmi. Pihenj!";
			link.l2.go = "exit";
			NextDiag.TempNode = "tonzag_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Kapitány, nagyon sajnálom, de én nem foglalkozom számokkal és számításokkal. Kérdezze meg van Merdent - ô ért az ilyesmihez, bár kétlem, hogy érdekelné, hogy elhagyja a fészkét.";
			Link.l1 = "Igaza van, Hercule. Találnom kell egy pénztárost...";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Kapitány, amikor Barbadoson voltam fogadós, csak rumot és élelmiszert vettem. És az ellátmány alatt rendes ételeket értek, nem kekszet és marhahúst. Sajnálom, de ez nem az én feladatköröm.";
			link.l1 = "Talán a hajómból kocsmát kellene csinálnunk... Csak vicceltem, Hercule. Mindegy, majd én megcsinálom.";
			link.l1.go = "exit";
		break;
		
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Hallgatlak téged.";
			Link.l1 = "A beszállásról van szó.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "A hajójáról van szó.";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "Eddig semmi.";
			Link.l8.go = "exit";
		break;

		case "Companion_TaskBoarding":
			dialog.Text = "Szóval mi a kívánságod?";
			Link.l1 = "Ne szállj fel az ellenséges hajókra. Vigyázz magadra és a legénységre.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Azt akarom, hogy szállj fel az ellenséges hajókra.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "Szóval mi a kívánságod?";
			Link.l1 = "Szeretném, ha nem cserélnéd el a hajódat egy másikra a beszállás után. Az túl értékes.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Amikor ellenséges hajókra szállsz fel, elviheted ôket magadnak, ha történetesen tisztességesek.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Aye-aye.";
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
			dialog.Text = "Aye-aye.";
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
            dialog.Text = "Mik a parancsai? ?";
            Link.l1 = "Maradjon itt!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Kövessetek és ne maradjatok le!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Változtasd meg a lôszered típusát.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Válaszd kia lôszer típusát:";
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
            dialog.Text = "Igen!";
            Link.l1 = "Pihenj.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Igen!";
            Link.l1 = "Pihenj.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Maga aztán szerencsés, kapitány. Örülök, hogy csatlakoztam hozzád, amikor még te, én és John együtt dolgoztunk. A cápa nyelje le a fejem, ha nem támogatlak ebben a vállalkozásban!";
			link.l1 = "Köszönöm, Hercule! Örülök, hogy igazam volt veled kapcsolatban.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Szóval, mikor indulunk?";
			link.l1 = "Kicsit késôbb. Most már fel kell készülnünk az útra.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "23");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tonzag_jailed":
			dialog.text = "Nagyjából semmit, Cap. Ha ennek köze lenne a mi ügyünkhöz, már rég a kínzóasztalon feküdtünk volna.\nMivel nem vittek minket azonnal kihallgatásra, úgy tûnik, nem sürgôs az ügy.\nEgyik sem csapda, vagy zsarolás.\nPár napig itt pácolnak minket anélkül, hogy bármit is megmagyaráznának. Aztán jönnek egy ajánlattal, amit elfogadunk.";
			link.l1 = "Személyes tapasztalat?";
			link.l1.go = "tonzag_jailed_1";
			link.l2 = "Nos, van rá mód, hogy most rávegyük ôket, hogy egy ilyen ajánlattal álljanak elô?";
			link.l2.go = "tonzag_jailed_2";
			locCameraFromToPos(-14.82, 0.92, 2.74, true, -60.00, -5.60, -22.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Természetesen. Gruoh-nak egyszer egy halott ember rokonai fizettek, hogy megkímélje ôt a trinidadi hóhér búcsúzó simogatásától.\nFizetett a parancsnoknak azért, hogy végigsétálhasson a fogdákon. Bevett gyakorlat - sokan fizetnek a katonáknak azért, hogy tanúk nélkül kínozhassák azokat, akik nem tudnak ellenállni.\nA férfi csendben és szenvedés nélkül halt meg. Tiszta és tisztességes munka.";
			link.l1 = "Gruoh? Ki az?";
			link.l1.go = "tonzag_jailed_1_1";
		break;
		
		case "tonzag_jailed_1_1":
			dialog.text = "Sajnálom, Cap. Rossz helyen és rossz idôben.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "Megpróbálhatjuk. Várjuk meg az etetési idôt, és váltok pár szót az ôrrel. Látod, még mindig nem tanultak meg rendesen keresni. Eh...";
			link.l1 = "Mi a baj?";
			link.l1.go = "tonzag_jailed_2_1";
		break;
		
		case "tonzag_jailed_2_1":
			dialog.text = "Furcsa érzés, Kapitány. Még elôérzetnek is nevezném. Elnézést, beszéljünk késôbb.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "tonzag_killed_hunters":
			dialog.text = "Lemaradtam valamirôl, kapitány?";
			link.l1 = "Ó, semmi különös, csak egy újabb nap a tengeren. Nézzenek oda, maga vén ördög! Elég nagy zûrzavart csináltál itt nekem.";
			link.l1.go = "tonzag_killed_hunters_1";
		break;
		
		case "tonzag_killed_hunters_1":
			dialog.text = "A vér lemosható hideg vízzel, kapitány. Beszélnünk kell.";
			link.l1 = "Gondolja? Kezdetnek nem ártana túlélni ezt a napot.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_Victory");
		break;
		
		case "tonzag_after_victory_helena":
			dialog.text = "Én is örülök, hogy látlak, Rumba. Kapitány, nem zavarlak, majd késôbb beszélünk.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HelenBoardingDialog1");
		break;
		
		case "tonzag_after_victory_mary":
			dialog.text = "Hé, Ginger. Kapitány, nem zavarok, majd késôbb beszélünk.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_MaryBoardingDialog1");
		break;
		
		case "tonzag_after_victory_alonso":
			dialog.text = "Kapitány, nem zavarom, majd késôbb beszélünk.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_drink":
			dialog.text = "Készen áll, hogy meghallgasson, kapitány?";
			link.l1 = "Itt az ideje, hogy beszélgessünk, Hercule. Most jöttem rá, hogy szinte semmit sem tudok rólad.";
			link.l1.go = "tonzag_drink_1";
		break;
		
		case "tonzag_drink_1":
			dialog.text = "Szóval itt az ideje, hogy megismerkedjünk. Hagyjuk ki a korai éveket, már csak azért is, mert ott nincs mirôl beszélni - egy gyôztes katona, egy legyôzött katona, egy dezertôr, egy martalóc... tudja, hogy megy ez.";
			link.l1 = "Igazából én nem, de eddig ez elég hétköznapinak hangzik.";
			link.l1.go = "tonzag_drink_2";
		break;
		
		case "tonzag_drink_2":
			dialog.text = "Egy ilyen katonai pálya után kevés karrierlehetôség kínálkozott számomra - bandita, akasztott ember, vagy a Holland Nyugat-indiai Társasághoz méltó ôr. Én az utóbbit választottam, mint érti.";
			link.l1 = "Ön is onnan dezertált?";
			link.l1.go = "tonzag_drink_3";
		break;
		
		case "tonzag_drink_3":
			dialog.text = "Épp ellenkezôleg, ott csináltam karriert. Ajánlatot kaptam a Társaság hírszerzô részlegének harci szárnyába, ahol megismertem a késôbbi feleségemet.";
			link.l1 = "Oké, eddig elég békés a történet... fôleg, ha nem gondolkodik túl sokat a hollandok módszereirôl.";
			link.l1.go = "tonzag_drink_4";
		break;
		
		case "tonzag_drink_4":
			dialog.text = "Nem fogsz hatalmas pénzt keresni azzal, hogy becsületes vagy, és a konkurenciát különbözô módokon harcolhatod ki. Igen, különleges módszerekkel dolgoztunk...";
			link.l1 = "Azt hiszem, tudom, mire gondolsz...";
			link.l1.go = "tonzag_drink_5";
		break;
		
		case "tonzag_drink_5":
			dialog.text = "Igen, ez bármi lehet: a kalózkodástól kezdve az áruraktárak felgyújtásáig. Végül a terv leleplezôdött, és feloszlattak minket... papíron, persze. Így született meg a Liga, amelyet csak a Társaság felsôbb szintjeinek kiválasztott vezetôi ismertek és irányítottak. Egy karibi törvényen kívüli számára, aki ér valamit, csak két lehetôség volt: kalózkodás vagy a Liga. És a Liga általában jobban fizetett\nA Liga többnyire még mindig a hollandoknak dolgozott, de mellékmegbízásokat is vállalhatott...";
			link.l1 = "A dolgok kezdenek tisztázódni...";
			link.l1.go = "tonzag_drink_6";
		break;
		
		case "tonzag_drink_6":
			dialog.text = "A Liga állt a Tortugai bohózat mögött. És aztán az a partraszálló csapat...";
			link.l1 = "Én is ezt gondoltam. De miért?";
			link.l1.go = "tonzag_drink_7";
		break;
		
		case "tonzag_drink_7":
			dialog.text = "Mert senki sem hagyja el élve a Ligát, és nem úszhatja meg szárazon azokat a dolgokat, amiket ott tettünk, kapitány. Vissza akartam vonulni, ezért megpróbáltam. Mint látja, nem túl sikeresen.";
			link.l1 = "Azt akarja mondani, hogy a volt kollégái hatalmas anyagi ráfordításokat vállaltak, majdnem száz embert dobtak ki, elégettek egy bránert, és kockáztatták a hadihajójukat, csak azért, hogy... megöljék magát dezertálásért?";
			link.l1.go = "tonzag_drink_8";
		break;
		
		case "tonzag_drink_8":
			dialog.text = "Több voltam, mint egy törpe a Ligában, kapitány. Túl sokat tudok róla. Engem nem lehet csak úgy elengedni, és ezt világossá kell tenniük, hogy senki másnak ne jusson eszébe elhagyni az üzletet... Már megpróbáltak elkapni engem... elég régen... Megölték a feleségemet és elcsúfítottak, még ha ez sokba is került nekik. Ennek a történetnek nincs happy endje, kapitány. Csak adjon egy parancsot, és én elhagyom a hajót, hogy egyedül intézzem el ôket, utoljára.";
			link.l1 = "Ne beszélj ostobaságokat, Hercule... És milyen szerepet játszott ebben Lucas Rodenburg? Biztosan benne volt ezekben az ügyekben! Az ön, vagy inkább az ô, 'szervezete', a Liga...";
			link.l1.go = "tonzag_drink_9";
		break;
		
		case "tonzag_drink_9":
			dialog.text = "Különbözô ügynökségek, kapitány. Igaz, gyakran ugyanannak a személynek engedelmeskedtek, és szorosan együttmûködtek. De Rodenburg különleges ügynökei pontos és hatékony csapásokat hajtottak végre, míg a Liga tömeges akciókat hajtott végre. És most mi lett a Ligával? A szervezet már nem létezik, ahogy látja: Én itt vagyok veled, John Murdock elment, Longway elszökött, Van Berg a tenger fenekén van, Rodenburgot kivégezték... Mégis, tartoztam annak a néhai gazembernek. Észrevett a Ligában, és amikor ki akartam lépni onnan, kihúzott egy komoly bajból, és a helyettesévé tett. Persze a többieknek ez nem tetszett, de senki sem mert neki ellenszegülni... Aztán az ismert körülmények között úgy döntött, hogy megszabadul Murdocktól és tôlem, de te közbeléptél, és a szolgálatodba fogadtál\nÉs így gondoltam, 'Itt a második esélyem, hogy szakítsak a múlttal...' Túljártál Rodenburgon, a Liga elvesztette a pártfogóját, nem volt többé veszély... De persze tévedtem... Öreg bolond... De elég ebbôl, kapitány. Gondoljuk át, mi legyen a következô lépés, persze csak akkor, ha tényleg nem tervezi, hogy az elsô kikötôben elenged.";
			link.l1 = "Nem tervezem. Gondolom, van valami terve?";
			link.l1.go = "tonzag_drink_10";
		break;
		
		case "tonzag_drink_10":
			dialog.text = "Igazából semmi különös. Soha nem fogjuk mindet kiirtani, de olyan nagy veszteségeket okozhatunk nekik, hogy nem éri meg nekik tovább üldözni engem... minket.";
			link.l1 = "És hogyan csináljuk ezt? Van táboruk?";
			link.l1.go = "tonzag_drink_11";
		break;
		
		case "tonzag_drink_11":
			dialog.text = "Egy nagy erôd? Aligha. Túl feltûnô és veszélyes lenne a Liga számára. És a veszteségek alatt nem az emberi veszteségekre gondolok - az emberekkel nem törôdnek, de az arany elvesztését nem fogják élvezni. A Társaságtól kapott pénz már nem jut el hozzájuk, igaz? Kétlem, hogy a Liga új mecénást talált volna, tehát valahonnan máshonnan kell aranyat kipréselniük.";
			link.l1 = "És melyik hely lenne az?";
			link.l1.go = "tonzag_drink_12";
		break;
		
		case "tonzag_drink_12":
			dialog.text = "Nem tudom, kapitány.";
			link.l1 = "Hercule, de az elôbb azt mondta, hogy éppen azért üldözik, mert túl sokat tud!";
			link.l1.go = "tonzag_drink_13";
		break;
		
		case "tonzag_drink_13":
			dialog.text = "Hadd gondolkozzam... Talán a Liga jelenleg a spanyolok ellen tevékenykedik. Ôk az elsôdleges jelöltek egy jó kis felrázásra. Ha már itt tartunk, Rodenburg mindig is jóban volt a kasztíliai kövér macskákkal. Néha hozzájuk irányította a Liga fiúkat különbözô munkákhoz, és mindig megtiltotta, hogy kárt okozzon nekik, amit egyébként a fiúk nem nagyon szerettek...";
			link.l1 = "Jó viszonyban, azt mondja? És mi van azzal a bizonyos Hidalgóval és az ujjával, akit a kocsmádba hurcoltattál velem?";
			link.l1.go = "tonzag_drink_14";
		break;
		
		case "tonzag_drink_14":
			dialog.text = "Ez egy különleges eset volt, egy mellékes megbízás. Ha bûntudata van, kapitány úr, megnyugodhat - az a Don azt kapta, amit megérdemelt... De én valami másról beszélek: miután a munkaadójuk eltûnt, a Liga ügynökei csak úgy engedhettek a vágyaiknak, és megpróbálhattak egy szolid szeletet lecsípni a spanyol tortából. Hála annak, hogy Rodenburg alatt együtt dolgoztak a spanyolokkal, tudják, hol és mit kell elvinniük.";
			link.l1 = "Hm... lehet, hogy igazad van. De amennyire én tudom, senki sem fékez be igazán a spanyol bankokba, a spanyolok ellen operálva a tengeren - ez már a szerencse hölgyén múlik... Talán keresnünk kéne valami spanyol vállalkozást? Egy gyárat?";
			link.l1.go = "tonzag_drink_15";
		break;
		
		case "tonzag_drink_15":
			dialog.text = "Érthetô feltételezés, kapitány... Van más nyomunk is?";
			link.l1 = "Hm... a hajó, amelyik ma megtámadott minket, délnek indult...";
			link.l1.go = "tonzag_drink_16";
		break;
		
		case "tonzag_drink_16":
			dialog.text = "Nem valószínû, hogy a kapitánya újra zavarni fog minket, de figyelmeztetnie kell a többieket, hogy a dolgok nem a tervek szerint alakultak, és talán a személyzetet máshová szállítja. Még valami?";
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.KnowMain")) {
				link.l1 = "Igen, volt egy baráti beszélgetésem a Tortuga börtönparancsnokkal... Említett valamit a szárazföldrôl.";
				link.l1.go = "tonzag_drink_know";
			} else {
				link.l1 = "Nem, semmi másról.";
				link.l1.go = "tonzag_drink_notknow";
			}
		break;
		
		case "tonzag_drink_know":
			dialog.text = "Kitûnô, kapitány! Dél, szárazföld, spanyolok - ez azt jelenti, hogy gyorsan megtaláljuk ôket. Elindulunk? És köszönöm, hogy meghallgattad a történetemet.";
			link.l1 = "Igen, eléggé szívhez szóló beszélgetés volt a végén... Vitorlát bontani!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ExitToSea");
		break;
		
		case "tonzag_drink_notknow":
			dialog.text = "Nem sok minden van, ami alapján elindulhatnánk. De a magunkfajtáknak ez elég. Mehetünk délnek? Keressünk egy spanyol kereskedelmi vállalkozást? És köszönöm, hogy meghallgattad a történetemet.";
			link.l1 = "Igen, eléggé szívhez szóló beszélgetés volt a végén... Vitorlát bontani!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ExitToSea");
		break;
		
		case "tonzag_dead":
			dialog.text = "Nézze, kapitány. Így mûködnek.";
			link.l1 = "És maga is így dolgozott?";
			link.l1.go = "tonzag_dead_1";
		break;
		
		case "tonzag_dead_1":
			dialog.text = "Menjünk, nézzük meg, mi van odabent.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_AfterDead");
		break;
		
		case "tonzag_afterminefight":
			dialog.text = "Mocskos ügy, kapitány. Ezt a barlangot kiürítettük, de ez biztosan nem az utolsó...";
			link.l1 = "Mi lesz a bányával, Hercule?! Az a sok ember odakint?! Ôket is 'kitakarították'! És mit jelentett az a gazember?";
			link.l1.go = "tonzag_afterminefight_1";
		break;
		
		case "tonzag_afterminefight_1":
			dialog.text = "Ezt majd késôbb megbeszéljük, kapitány. A parancsnokuk túlélte, ki kell hallgatnunk.";
			link.l1 = "És mi van, ha nem tud semmit?";
			link.l1.go = "tonzag_afterminefight_2";
		break;
		
		case "tonzag_afterminefight_2":
			dialog.text = "Tud valamit. Gondolj bele - vártak ránk, kivitték az összes aranyat, és eltüntették a tanúkat. Ez azt jelenti, hogy volt egy tervük. Körül akarok nézni itt, és késôbb magam viszem a gazembert a hajóra. Te is tartsd nyitva a szemed; lehet, hogy túlságosan elhamarkodottan cselekedtek, és valamit kihagytak.";
			link.l1 = "Rendben, de ha visszamegyünk a hajóra, komoly beszélgetés vár ránk!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			locations[FindLocation("LosTeques_town")].locators_radius.reload.gate_back = 1.0;
			DeleteAttribute(&locations[FindLocation("LosTeques_town")], "locators_radius.reload.reload1_back");
			AddDialogExitQuestFunction("Tonzag_PrepareJournal");
		break;
		
		case "tonzag_in_hold":
			dialog.text = "Jó hírek, kapitány.";
			link.l1 = "Semmi jót nem látok a helyzetünkben, Hercule. Menjünk, négyszemközt kell beszélnünk.";
			link.l1.go = "tonzag_in_hold_1";
		break;
		
		case "tonzag_in_hold_1":
			dialog.text = "Szóval így áll a dolog, mi? Igenis, kapitány.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_EnterAlonso");
		break;
		
		case "tonzag_drink_again":
			dialog.text = "Úgy látom, komoly beszélgetés elôtt állunk, kapitány.";
			link.l1 = "Igen, és én leszek az, aki beszélni fog. Elôször is, nem gondolja, hogy van itt egy bizonyos tendencia? Hullák halmai követnek minket, bárhová is megyünk! Elôször kapunk egy adag grapeshotot a gyomrunkba, és másnap több mint száz ember, jó és kevésbé jó, meghal... Még csak tengeri csatának sem nevezhetem! Néhány napja egy települést semmisítettünk meg, ma pedig azzal járultunk hozzá a növekvô halomhoz, hogy lemészároltunk egy csomó embert a bányákban.";
			link.l1.go = "tonzag_drink_again_1_1";
		break;
		
		case "tonzag_drink_again_1_1":
			dialog.text = "";
			link.l1 = "Természetesen aggódom a kilátás miatt, hogy a halom holnapra hegyekké nô, de ami igazán megrémít, hogy ez a sok vér egyetlen ember miatt folyik. És ez a személy jelentôs pozíciót tölt be a legénységemben!";
			link.l1.go = "tonzag_drink_again_1";
		break;
		
		case "tonzag_drink_again_1":
			dialog.text = "";
			link.l1 = "Másodszor, hazudtál nekem, Hercule. Egy dezertôr sem éri meg azt a fáradságot, amit a volt kollégái a likvidálásába fektetnek. Mit kiabált a foglyunk a bányában? Áruló? Porto Bello? Gruoh? Valamit tettél, Hercule, és ezúttal az igazságot akarom.";
			link.l1.go = "tonzag_drink_again_2";
		break;
		
		case "tonzag_drink_again_2":
			dialog.text = "Az igazat? Az igazság az, kapitány, hogy dezertáltam, a feleségemmel, Gruoh-val együtt. Madame Tonzag nem akarta elhagyni a Ligát; szerette azt az életet, de engem még jobban szeretett. Úgy volt, hogy egy spanyol hidalgóról gondoskodunk, de ô jobb ajánlatot tett. Ez volt a mi esélyünk, és mindketten beleegyeztünk, hogy a szolgálatába álljunk. A Liga persze azt hitte, hogy elpusztultunk egy küldetésen, és egy második csoportot küldött Porto Bellóba, hogy befejezzék a munkát, és bosszút álljanak.";
			link.l1 = "És mindannyiukat megölték?";
			link.l1.go = "tonzag_drink_again_3";
		break;
		
		case "tonzag_drink_again_3":
			dialog.text = "Elôször megölték Gruoh-t és eltorzítottak engem. A hidalgo nem akart többé semmit tenni velem, és kidobott. Ekkor talált rám Rodenburg...";
			link.l1 = "És most hogy bízzak meg benned? Dezertáltál a hadseregbôl, cserbenhagytad a Ligát, és megölted a saját társaidat! Ha eljön a megfelelô pillanat, te is elárulsz engem?";
			link.l1.go = "tonzag_drink_again_4";
		break;
		
		case "tonzag_drink_again_4":
			dialog.text = "Igen, dezertáltam, megszegtem a szerzôdést, megöltem néhány tucat Ligatagot. De megtanultam a leckét, kapitány. És különben is, egy halott ember nem árulhat el senkit, én pedig már régóta halott vagyok, Porto Bello óta. És talán ezért olyan nehéz most megölni engem.";
			link.l1 = "Ennyi elég mára. Úgy érzem, még mindig nem mondtál el mindent.";
			link.l1.go = "tonzag_drink_again_5";
		break;
		
		case "tonzag_drink_again_5":
			dialog.text = "Majd én magam intézem el a foglyot, vagy szeretnél csatlakozni?";
			link.l1 = "Gyerünk, menjünk. Én magam fogom kihallgatni.";
			link.l1.go = "tonzag_drink_again_hold";
			link.l2 = "Nem, az ilyen dolgok nem az én dolgom. Fél óra múlva találkozunk a kabinomban!";
			link.l2.go = "tonzag_drink_again_cabin";
		break;
		
		case "tonzag_drink_again_hold":
			DialogExit();
			
			NextDiag.CurrentNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_ReturnToHold");
		break;
		
		case "tonzag_drink_again_cabin":
			DialogExit();
			
			NextDiag.CurrentNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_ReturnToCabin");
		break;
		
		case "tonzag_hold":
			dialog.text = "Ki a fônök most? Arno?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog1");
		break;
		
		case "tonzag_hold_1":
			dialog.text = "Az a söpredék került hatalomra? Nem tartott sokáig, hogy egy közönséges banditává degradálódjatok...";
			link.l1 = "Ki az az Austin?";
			link.l1.go = "tonzag_hold_2";
		break;
		
		case "tonzag_hold_2":
			dialog.text = "Austin bandája arról volt híres, hogy szabad kapitányokat csalt a vadonba, feldarabolta ôket, és a holttestüket teljesen megfosztotta minden pénzüktôl és csecsebecséiktôl. Jó üzlet, és kalandvágyókból sincs hiány, így senkit sem zavart. Egy kapitánnyal azonban akadt egy kis bökkenôjük, így kénytelen volt a társaság szárnyai alá venni a legénységét. Pórázon tartottuk, és csak akkor engedtük el, ha gyorsan és egyszerûen kellett megoldani a problémákat.";
			link.l1 = "Kétlem, hogy egy ilyen emberrel alkut tudnék kötni.";
			link.l1.go = "tonzag_hold_3";
		break;
		
		case "tonzag_hold_3":
			dialog.text = "Az biztos. Ha most ô és az emberei irányítják a dolgokat, hamarosan a Liga is csak egy újabb bandává válik.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog3");
		break;
		
		case "tonzag_after_hold":
			dialog.text = "Érdekes beszélgetést folytattunk.";
			link.l1 = "Szeretném tudni, hogy mennyi igaz ebbôl... Mi van a Porto Bello-i mészárlással? Ha nem hazudott, az azt jelenti, hogy amikor legutóbb beszélgettünk, megint kihagyott néhány fontos tényt az illusztris életrajzából.";
			link.l1.go = "tonzag_after_hold_1";
		break;
		
		case "tonzag_after_hold_1":
			dialog.text = "Forró volt Porto Bellóban, kapitány. Az életemért harcoltam, a munkaadóm életéért, a feleségem életéért. Nem volt idôm megszámolni az elesetteket és meggyászolni minden parasztot, aki rosszkor bukkant fel az utcán.";
			link.l1 = "Ebben a fontossági sorrendben?";
			link.l1.go = "tonzag_after_hold_2";
		break;
		
		case "tonzag_after_hold_2":
			dialog.text = "Nem, természetesen nem. Az övé az elsô. Mindig az övé.";
			link.l1 = "Mit gondolsz? Menjünk Caracasba?";
			link.l1.go = "tonzag_after_hold_3";
		break;
		
		case "tonzag_after_hold_3":
			dialog.text = "Én személy szerint nem, kapitány. És én is azt tanácsolnám, hogy ne tegye. A Liga számára ön már nem ellenség, én pedig nem érdeklem ôket, legalábbis egyelôre, amíg az önök szolgálatában állok. Ráadásul mélyen legbelül van ez a rossz érzésem\nNem lesz jó, ha odamegyünk. Nagyon rossz. Ennek a történetnek nincs happy endje. De én a végsôkig veled leszek, kapitány.";
			link.l1 = "Megfontolom.";
			link.l1.go = "exit";
			
			if (CheckCharacterItem(pchar, "MerdokArchive")) {
				link.l1.go = "tonzag_after_hold_4";
			}
			
			AddDialogExitQuestFunction("Tonzag_GoToCaracas");
		break;
		
		case "tonzag_after_hold_4":
			dialog.text = "";
			link.l1 = "Egyébként igazad volt - nem sikerült elég jól megtisztítaniuk a bányát. Nézze.";
			link.l1.go = "tonzag_after_hold_5";
		break;
		
		case "tonzag_after_hold_5":
			dialog.text = "Egy tiszt naplója... titkosítva, de ez egy régi rejtjel, tudom\nNem érdekes, úgy tûnik. A foglyunk naplója volt. Most már világos, hogy miért volt hajlandó beszélni. Nézd csak - egy elrejtett kincsre utaló jelek! A gazember egyértelmûen visszavonulást tervezett, és bármelyik pillanatban kész volt elszökni!";
			link.l1 = "És hol van ez a rejtett hely?";
			link.l1.go = "tonzag_after_hold_6";
		break;
		
		case "tonzag_after_hold_6":
			dialog.text = "Ismeri azt a szigetet, kapitány. A vizein végeztél Van Berddel.";
			link.l1 = "Rendben, nincs túl messze, nézzük meg! Ami Caracast illeti, még nem döntöttem el, de azt hiszem, van egy hónapunk.";
			link.l1.go = "tonzag_after_hold_7";
		break;
		
		case "tonzag_after_hold_7":
			dialog.text = "Ahogy óhajtja, kapitány. A végsôkig veled leszek.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CreateLoot");
		break;
		
		case "tonzag_after_drink":
			dialog.text = "Vége van, kapitány. Austin jelenleg Caracasban van; azt hiszem, van egy hónapunk.";
			link.l1 = "Az elsô dolgok a legfontosabbak. Mit mondott a fogoly? Ki ez az Austin? És miért menjünk Caracasba?";
			link.l1.go = "tonzag_after_drink_1";
		break;
		
		case "tonzag_after_drink_1":
			dialog.text = "Austin bandája arról volt híres, hogy szabad kapitányokat csalt a vadonba, feldarabolta ôket, és a holttestüket teljesen megfosztotta minden pénzüktôl és csecsebecséiktôl. Jó üzlet, és kalandvágyókból sincs hiány, így senkit sem zavart. Egy kapitánnyal azonban akadt egy kis bökkenôjük, így kénytelen volt a társaság szárnyai alá venni a legénységét. Pórázon tartottuk, és csak akkor engedtük el, ha gyorsan és egyszerûen kellett megoldani a problémákat.";
			link.l1 = "Kétlem, hogy egy ilyen emberrel alkut tudnék kötni.";
			link.l1.go = "tonzag_after_drink_2";
		break;
		
		case "tonzag_after_drink_2":
			dialog.text = "Az biztos. Ha most ô és az emberei irányítanak, akkor a Liga hamarosan csak egy újabb bandává válik. De én nem mennék Caracasba, kapitány.";
			link.l1 = "Komolyan? Félsz?";
			link.l1.go = "tonzag_after_drink_3";
		break;
		
		case "tonzag_after_drink_3":
			dialog.text = "Ez nem így van, kapitány. Mielôtt belehalt a sebeibe, a fogoly elárulta, hogy ön már nem ellensége a Ligának, én pedig nem érdeklem ôket, legalábbis egyelôre, amíg a szolgálatában állok. Úgy tûnik, a Ligának új, befolyásos pártfogója van, aki elrendelte, hogy hagyjanak minket békén\nés Caracas... Van egy rossz érzésem a lelkem mélyén... Rossz lesz, ha odamegyünk. Nagyon rossz. Ennek a történetnek nincs happy endje. De én a végéig veled leszek, kapitány.";
			link.l1 = "Meggondolom. Természetesen szeretném egyszer s mindenkorra megoldani ezt a történetet, de talán igaza van. Kétlem, hogy az elmúlt hét eseményei után újra közeledni mernének hozzánk.";
			link.l1.go = "exit";
			
			if (CheckCharacterItem(pchar, "MerdokArchive")) {
				link.l1.go = "tonzag_after_drink_4";
			}
			
			AddDialogExitQuestFunction("Tonzag_GoToCaracas");
		break;
		
		case "tonzag_after_drink_4":
			dialog.text = "";
			link.l1 = "Egyébként igazad volt - nem sikerült elég jól megtisztítaniuk a bányát. Nézze.";
			link.l1.go = "tonzag_after_drink_5";
		break;
		
		case "tonzag_after_drink_5":
			dialog.text = "Egy tiszt naplója... titkosítva, de ez egy régi rejtjel, tudom\nNem érdekes, úgy tûnik. A foglyunk naplója volt. Nézd csak - egy elrejtett kincsre utaló jelek! A gazember egyértelmûen visszavonulást tervezett, és bármelyik pillanatban kész volt elszökni!";
			link.l1 = "És hol van ez a rejtett hely?";
			link.l1.go = "tonzag_after_drink_6";
		break;
		
		case "tonzag_after_drink_6":
			dialog.text = "Ismeri azt a szigetet, kapitány. A vizein végeztél Van Berddel.";
			link.l1 = "Rendben, nincs túl messze, nézzük meg! Ami Caracast illeti, még nem döntöttem el, de azt hiszem, van egy hónapunk.";
			link.l1.go = "tonzag_after_drink_7";
		break;
		
		case "tonzag_after_drink_7":
			dialog.text = "Ahogy óhajtja, kapitány.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CreateLoot");
		break;
		
		case "tonzag_church":
			dialog.text = "Várjon, kapitány. Egyedül megyek oda.";
			link.l1 = "És miért? Most hôsiesnek érzi magát? Túl késô; maga csinálta ezt a mocskot, de nekünk együtt kell eltakarítanunk.";
			link.l1.go = "tonzag_church_1";
		break;
		
		case "tonzag_church_1":
			dialog.text = "Nem kell megfizetnie a hibáimért, kapitány. Igaza volt - bárhová megyek, emberek halnak meg, és ártatlan vér folyik. Ha együtt lépünk be abba a templomba, az egy újabb Porto Bello lesz, és azt nem akarom.";
			link.l1 = "Mi történt ott valójában?";
			link.l1.go = "tonzag_church_2";
		break;
		
		case "tonzag_church_2":
			dialog.text = "Egy mészárlás. Vissza akartam vonulni, kapitány. Fogni akartam az aranyat, a feleségemet, és hazamenni Carcassonne-ba. Tudtam, hogy a Liga több embert fog küldeni, hogy befejezzék a munkámat, és bôkezû elôleget fogadtam el új patrónusomtól. Ezután már csak az volt hátra, hogy a városôrséget a korábbi bûntársaim és az új munkaadóm ellen uszítsam. Ebben a felfordulásban kellett eltûnnöm a pénzzel, és talán, ha az idôm engedte, kirabolni néhány kövér macskát Porto Bellóban.";
			link.l1 = "Jó terv, bár én másképp csináltam volna. Túl sok minden elromolhatott volna.";
			link.l1.go = "tonzag_church_2a";
			link.l2 = "Én sem vagyok egy angyal, de az ön megközelítése még engem is megborzongat. Meglep, hogy még nem árultál el engem, ahogy a Ligát, a Hidalgót, sôt még a saját feleségedet is.";
			link.l2.go = "tonzag_church_2a";
		break;
		
		case "tonzag_church_2a":
			dialog.text = "Minden, ami elromolhatott, el is romlott. Hiba volt a kormányzó palotája felé lövöldözni. Magát a kormányzót alig karcolta meg, de gyönyörû lányának, mint hallottam, mindkét lábát térd alatt amputálni kellett, hogy megmentsék az életét. A válasz szörnyû volt - vérfürdô; rengeteg ember halt meg, kapitány. Most az események utolsó élô szemtanúját látja, és nemrég maga is levágott egy másikat.";
			link.l1 = "Magyarázza el.";
			link.l1.go = "tonzag_church_3";
		break;
		
		case "tonzag_church_2b":
			dialog.text = "Ha Madame Tonzag még élne, habozás nélkül elárultam volna önt, kapitány úr. Én egy élô halott vagyok, aki követi önt, mert nincs más helyem ezen a világon. Most az események utolsó élô tanúját látja, és nemrég maga is levágott egy másikat.";
			link.l1 = "Magyarázza el.";
			link.l1.go = "tonzag_church_3";
		break;
		
		case "tonzag_church_3":
			dialog.text = "Bocsásson meg, kapitány, hogy nem mondtam el mindent útközben. Amikor elôször találkoztunk, azt hittem, maga is csak egy olyan szemétláda, mint én. És tudja, mi volt az elsô dolog, amit tettem? Elküldtem, hogy takarítson utánam - hogy megölje azt a spanyol Dont, akit kezdetben nem akartam megölni, aztán úgy döntöttem, hogy elárulom. Az a Hidalgo, Rodriguez...";
			link.l1 = "És miért volt szükséged az ujjára?";
			link.l1.go = "tonzag_church_4";
		break;
		
		case "tonzag_church_4":
			dialog.text = "Semmi trükk. Csak egy teszt, kapitány. Évente tucatnyi ilyen fiatal gyilkosokat toborzunk, mint maga. Csak néhányan mentek át az alapvetô becsületességi teszten, és még ôk is meghaltak az elsô bevetéseken. Nem kellett volna túlélnie a mûveletet Fleetwood naplójával. Azt terveztem, hogy egyszerûen bemegyek a házba, végzek a túlélôkkel, és elviszem a naplót.";
			link.l1 = "Ha jól emlékszem, a történet kissé másképp alakult.";
			link.l1.go = "tonzag_church_5";
		break;
		
		case "tonzag_church_5":
			dialog.text = "Így történt, kapitány. Nem tudom, mi késztetett arra, hogy segítsek neked, de olyan életörömmel harcoltál a Rókák ellen, hogy még engem is megfertôztél vele, ha csak rövid idôre is. A végén, tudtán kívül, megmentettél engem. Nem tartozik nekem semmivel, kapitány. És nem engedem be oda. Ez az én dolgom, az én megváltásom.";
			link.l1 = "Ahogy óhajtja, Hercule. Fájdalmas elveszíteni egy ilyen harcost, de te már régen elvesztetted magad, és nem érsz meg több kiontott vért. Nekem sem tartozol semmivel, és remélem, hogy abban a kis templomban találsz megváltást.";
			link.l1.go = "tonzag_church_bad";
			link.l2 = "Szép beszéd, Hercule. Menj a pokolba! Ha nem vetted volna észre, a te problémáid mostanában az enyémekké váltak. Maga az én tisztem, és csak én döntöm el, hogy megérdemli-e a megbocsátást vagy sem. Úgyhogy még egy kicsit velünk kell maradnod, és a legénységem tagjaként bátorsággal kiérdemelned a megváltást!";
			link.l2.go = "tonzag_church_good";
		break;
		
		case "tonzag_church_bad":
			dialog.text = "Köszönök mindent, kapitány. Viszontlátásra!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchBad");
		break;
		
		case "tonzag_church_good":
			dialog.text = "Igenis, kapitány!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchGood");
		break;
		
		case "tonzag_afterchurchfight":
			dialog.text = "Sok gazembert láttam már, kapitány, de most elôször éreztem, hogy a rémület csavarodik bennem. Mit gondolsz: ha egy kisebb szörnyeteg megöl egy nagyobbat, az számít a megváltásnak?";
			link.l1 = "Vízzel hígítják a rumot? Szólj, ha rájöttél. Menjünk, itt végeztünk.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ResetTonzag");
		break;

	}
}