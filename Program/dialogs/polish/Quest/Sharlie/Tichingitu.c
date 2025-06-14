// Тичингиту - индеец-офицер
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
			dialog.text = "Czego chcesz?";
			link.l1 = "Niczego.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Tichingitu":
			DelLandQuestMark(npchar);
			dialog.text = "Czego chcesz, blada twarz? Tichingitu nie ma ci nic do powiedzenia.";
			link.l1 = "Twoje imię to Tichingitu? Hm. Słuchaj, wojowniku, nie przyszedłem tu, żeby się na ciebie gapić. Przyszedłem zadać ci pytanie: Dlaczego wtargnąłeś do domu tego grubego gościa?";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "";
			link.l1 = "Nic nie mówisz? Niezbyt mądrze z twojej strony. Zostaniesz powieszony za kradzież i wszystko inne, co uczyniłeś. Powiedz mi, dlaczego popełniłeś taki czyn, a może będę w stanie ci pomóc.";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "Tichingitu przybył do miasta bladych twarzy przez wiele, wiele dróg, przez wielką wodę, z wielkich lasów i bagien. Tichingitu zmęczony i chciał jeść. Tichingitu umiera z głodu. Nikt nie chce pomóc Tichingitu. Krzyczą, 'Odejdź, czerwonoskóry psie'. Właściciel karczmy wyrzuca Indianina jak parszywego psa. Tichingitu chce jeść.";
			link.l1 = "Do diabła, ale dlaczego przybyłeś do tej osady z... twojego lasu?";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "„Tichingitu wyrzucony z plemienia tubylców. Tichingitu posprzeczał się z szamanem plemienia, szaman powiedział wodzowi, Szaman przeklął Tichingitu, Tichingitu opuścił plemię, daleko, daleko od ziemi przodków. Tichingitu bez domu, bez broni, bez niczego.”";
			link.l1 = "Tak to właśnie nazywam nieszczęściem. Czemu walczyłeś z własnymi ludźmi?";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Szaman plemienia złym człowiekiem. Mówi, że zły duch zamieszkał w ciele żony. Żona musi umrzeć. Moja żona po prostu chora, żaden duch nie zamieszkał. Tichingitu leczy żonę, szaman zabija żonę. Tichingitu sprzeciwia się szamanowi, wszyscy sprzeciwiają się Tichingitu, Tichingitu odchodzi.";
			link.l1 = "Próbowałeś uratować swoją żonę? Dlatego cię wyrzucili z wioski?";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Tak, blada twarzy. Tichingitu nie ma wyboru. Albo kraść, albo umrzeć z głodu...";
			link.l1 = "Cóż, powiadam... Stryczek za kilka nędznych monet skradzionych przez głodnego człowieka... Tichingitu, spróbuję ci pomóc. Znam Fadeya, tego krzepkiego człowieka, do którego domu się wkradłeś. Może uda mi się coś zrobić... Pójdę porozmawiać z komendantem.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
			pchar.questTemp.Sharlie.Tichingitu = "commandante";
			AddLandQuestMark(characterFromId("BasterJailOff"), "questmarkmain");
			AddQuestRecord("Tichingitu", "2");
		break;
		
		case "Tichingitu_wait":
			dialog.text = "Tichingitu czeka. Indianin nie boi się śmierci. Szaman przeklina Tichingitu, Tichingitu musi umrzeć.";
			link.l1 = "Jeszcze nie wszystko stracone. Spróbuję pomóc...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
		break;
		
		case "Tichingitu_6":
			DelLandQuestMark(npchar);
			dialog.text = "Tichingitu czeka. Indianin nie boi się śmierci. Szaman przeklął Tichingitu, Tichingitu musi umrzeć.";
			link.l1 = "Nie ma potrzeby być pesymistą. Twoje uwięzienie dobiegło końca. Pomogłem ci odzyskać wolność.";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			dialog.text = "Blada twarz żartuje? Tichingitu wolny?";
			link.l1 = "Nie, nie żartuję. Zaraz otworzą twoją celę i wypuszczą cię. Chodź za mną, wyprowadzę cię z więzienia.";
			link.l1.go = "Tichingitu_8";
		break;
		
		case "Tichingitu_8":
			DialogExit();
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			DoQuestReloadToLocation("BasTer_exittown", "rld", "aloc9", "TichingituFree"); // 170712
			pchar.quest.FreeTichingituOver.over = "yes"; //снять таймер
			if (GetHour() > 17.0)
			{
				WaitDate("", 0, 0, 0, 13, 0);
				RecalculateJumpTable();
				RefreshWeather();
				RefreshLandTime();
			}
			if (GetHour() < 8.0)
			{
				WaitDate("", 0, 0, 0, 7, 0);
				RecalculateJumpTable();
				RefreshWeather();
				RefreshLandTime();
			}
		break;
		
		case "Tichingitu_9":
			dialog.text = "";
			link.l1 = "Już jesteś wolny. Idź, Tichingitu, uważaj, żeby nic więcej nie ukraść i nie wpaść w kolejne kłopoty! Lepiej znajdź jakąś indiańską wioskę i zamieszkaj z własnymi ludźmi, nie sądzę, żeby byli przeciwko przyjęciu ciebie.";
			link.l1.go = "Tichingitu_10";
		break;
		
		case "Tichingitu_10":
			dialog.text = "Tichingitu nie odejdzie. Pan uratował życie Tichingitu. Tichingitu zostanie. Życie Tichingitu należy do pana.";
			link.l1 = "Hę? O czym ty mówisz? Jaki pan, jakie życie? Nie rozumiesz, co mówię? Jesteś wolny! Idź!";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "Indianin ma dług, biały panie. Tichingitu służy ci wiernie i prawdziwie. Tichingitu wie, jak walczyć. Tichingitu umrze w bitwie za pana. On zostaje.";
			link.l1 = "O Boże! Do diabła... Jakim ja jestem dla ciebie panem, Tichingitu? Pomogłem ci, by nie uczynić cię niewolnikiem.";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "Tichingitu nie jest niewolnikiem. Tichingitu jest wolnym Indianinem. Tichingitu chce ci służyć. Tichingitu wie, jak walczyć, każdy pies zginie, zanim zbliży się do pana. Tichingitu wie, jak czyścić i ładować muszkiet. Tichingitu potrafi strzelać z muszkietu.";
			link.l1 = "Jesteś niereformowalny... Chociaż... Wiesz co, Tichingitu? To niezły pomysł. Potrzebuję lojalnych ludzi, a ty nie wydajesz się być złym człowiekiem. Poza tym wiesz, jak strzelać z muszkietu. A co zamierzasz robić sam? Skończysz kradnąc coś innego, a następnym razem na pewno cię powieszą... Dobrze, możesz zostać. Ale pamiętaj: życie ze mną nie będzie spokojne.";
			link.l1.go = "Tichingitu_13";
			link.l2 = "Dobrze, dość. Idź w pokoju, czerwonoskóry bracie. Niech twoi bogowie czuwają nad tobą!";
			link.l2.go = "Tichingitu_exit";
		break;
		
		case "Tichingitu_exit":
			DialogExit();
			AddQuestRecord("Tichingitu", "5");
			CloseQuestHeader("Tichingitu");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.Sharlie.Tichingitu");
			pchar.systeminfo.tutorial.Fighter = true;
		break;
		
		case "Tichingitu_13":
			dialog.text = "Tichingitu nie boi się niczego, biały panie. Tichingitu będzie zadowolony służyć tobie. Tichingitu wierny do ostatniego tchu.";
			link.l1 = "Dobrze. Witamy w załodze, Tichingitu!";
			link.l1.go = "Tichingitu_hire";
		break;
		
		case "Tichingitu_hire":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			LAi_SetImmortal(npchar, false);
			npchar.quest.OfficerPrice = sti(pchar.rank)*20;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.CanTakeMushket = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Tichingitu_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			DeleteAttribute(pchar, "questTemp.Sharlie.Tichingitu");
			pchar.OfficerAttRange = 35.0;
			
			AddQuestRecord("Tichingitu", "4");
			CloseQuestHeader("Tichingitu");
			// Sinistra - Начало квеста "Знакомство с индейцами"
			string sModel = "Miskito_"+(rand(5)+1);
			sld = GetCharacter(NPC_GenerateCharacter("ListKakao", sModel, "man", "man", 1, PIRATE, -1, false, "quest"));
			sld.name = "Cocoa";
			sld.lastname = "Leaf";
			GiveItem2Character(sld, "blade_01");
			EquipCharacterByItem(sld, "blade_01");
			AddItems(sld, "jewelry53", rand(20)+180);
			AddItems(sld, "cannabis1", 3);
			GiveItem2Character(sld, "indian_10");
			GiveItem2Character(sld, "talisman11");
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "ZsI_ListKakao";
			ChangeCharacterAddressGroup(sld, "BasTer_ExitTown", "item", "item3");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			//LaunchTutorial("Fighter", 1);
		break;
		
	//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Tichingitu_officer":
			dialog.text = "Tichingitu słucha cię, Kapitanie "+pchar.name+"!";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Tichingitu, zamierzam wyruszyć do starej indiańskiej wioski zwanej Tayasal. Nie będę kłamać, to niezwykle niebezpieczna podróż i bardzo nietypowa: przez idol teleportacyjny. Ty... Czy dołączysz do mnie?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Tichingitu, daj mi pełen raport o statku.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Chcę, abyś kupował pewne towary za każdym razem, gdy zacumujemy.";
				Link.l12.go = "QMASTER_2";
			}

			Link.l1 = "Słuchaj mojego rozkazu!";
            Link.l1.go = "stay_follow";
			link.l2 = "Nic w tej chwili. Spocznij!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Raport z okrętu? Tichingitu nie ma raportu, panie. Tylko broń i ubrania. Tichingitu nie wziął raportu znikąd.";
			Link.l1 = "Dobrza, nieważne.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Mistrzu, Tichingitu nigdy nie wszedłby do kolonii bez ciebie. Gdy Tichingitu wchodzi do sklepu - wszyscy myślą, że Tichingitu znów jest złodziejem. Potem, więzienie.";
			link.l1 = "Tak, pewnie masz rację. Znowu ta więzienna sprawa. Poza tym, nikt nigdy nie uwierzy, że jesteś kwatermistrzem.";
			link.l1.go = "exit";
		break;
		
		case "stay_follow":
            dialog.Text = "Jakie masz rozkazy?";
            Link.l1 = "Zostań tutaj!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Chodź za mną i nie zostawaj w tyle!";
            Link.l2.go = "Boal_Follow";
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Musisz zmienić rodzaj amunicji do swojej broni palnej.";
					Link.l3.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Zmień rodzaj amunicji w swojej muszkiecie.";
					Link.l4.go = "SetMusketBullets";
				}
					Link.l5 = "Zmień swoją priorytetową broń do walki.";
					Link.l5.go = "SetPriorityMode";
					Link.l6 = "Chcę, abyś trzymał się z dala od celu.";
					Link.l6.go = "TargetDistance";
			}	
		break;
		
		case "SetGunBullets":
			Dialog.Text = " Jaka amunicja, biały panie? ";
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
			Dialog.Text = "Jaka amunicja, biały panie?";
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
			Dialog.Text = "Na początku walki użyje?";
			Link.l1 = "Ostrza";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Muszkietu";
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
            dialog.Text = "Zmiana planu!";
            Link.l1 = "Spocznij.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Zmiana planu!";
            Link.l1 = "Spocznij.";
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "Jak daleko, Kapitanie? Powiedz Tichingitu, ile jardów, ale nie więcej niż dwadzieścia.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Kapitanie, wybacz Tichingitu, ale nie rozumiem ciebie.";
				link.l1 = "Przepraszam, mój błąd...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = " Tichingitu stoi bezczynnie, nie rusza się.  Czy tego właśnie chcesz, kapitanie?";
				link.l1 = "Tak, dokładnie tak.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Tichingitu nie może pozostać dalej niż dwadzieścia jardów od celu. Wtedy chybia.";
				link.l1 = "Dobrze, trzymaj dystans na dwadzieścia jardów.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Tichingitu rozumie wszystko. Tichingitu zajmie pozycję, jak powiesz.";
			link.l1 = "Dobrze.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Życie Tichingitu od dawna stało się życiem mojego Kapitana. Indianin nie zapomni, co Kapitan zrobił dla Tichingitu. Tichingitu pójdzie za nim, gdzie Kapitan powie, bez pytań, bez wahania.";
			link.l1 = "Dziękuję, mój przyjacielu!";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Kiedy wyruszamy?";
			link.l1 = "Trochę później. Na razie musimy przygotować się do podróży.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "21");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tonzag_jailed":
			dialog.text = "Płacimy białemu człowiekowi sto dublonów, odchodzimy i swobodnie wykonujemy nasze zadanie.";
			link.l1 = "A co, jeśli znowu nas złapią?";
			link.l1.go = "tonzag_jailed_1";
			locCameraFromToPos(-16.78, 1.88, -1.70, true, -5.00, -6.10, -20.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Płacimy tysiąc dublonów.";
			link.l1 = "Cynicznie, ale dość przenikliwie.";
			link.l1.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "Gwadelupa jest gorsza.";
			link.l1 = "Niby czemu?";
			link.l1.go = "tonzag_jailed_3";
		break;
		
		case "tonzag_jailed_3":
			dialog.text = "Tam chcą powiesić tylko Tichingitu. Tutaj, chcą powiesić razem z Tichingitu. Nie jest tak źle.";
			link.l1 = "To już było naprawde cyniczne z twojej strony!";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "Strzał z bliska. Kapitanie, staruszek jest silny, możemy go ocalić, jeśli szybko zadziałamy.";
			link.l1 = "...";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
			AddDialogExitQuestFunction("Tonzag_JailFear");
		break;
		
		case "tonzag_dead":
			dialog.text = "Białas nie zna litości. Wielu z moich, Kapitanie. Tak wielu. Ale twoi więcej.";
			link.l1 = "Czy to twoje plemię?";
			link.l1.go = "tonzag_dead_1";
		break;
		
		case "tonzag_dead_1":
			dialog.text = "Niektóre... niektóre moje.";
			link.l1 = "Trzymaj się, przyjacielu.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
	// Тичингиту говорит о том, что нужно спасти Делюка
		case "Del_Deluck":
			dialog.text = "Jeszcze sto dublonów?";
			link.l1 = "Co? Pytasz, czy znowu zapłacę za uwolnienie Deluca z więzienia?";
			link.l1.go = "Del_Deluck_1";
		break;
		
		case "Del_Deluck_1":
			dialog.text = "Tak.";
			link.l1 = "Sam nie jestem pewien... Co o tym sądzisz?";
			link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			dialog.text = "Powinniśmy go wykupić.";
			link.l1 = "To honorowe. Nigdy nie zostawiaj swojego z tyłu, co?";
			link.l1.go = "Del_Deluck_3";
		break;
		
		case "Del_Deluck_3":
			dialog.text = "Albo zostaw go. Zostaw słabego jaguarowi w dżungli.";
			link.l1 = "Komu?";
			link.l1.go = "Del_Deluck_4";
		break;
		
		case "Del_Deluck_4":
			dialog.text = "Wielki kot.";
			link.l1 = "Tichingitu, mam trudności ze zrozumieniem ciebie. Po prostu powiedz mi: co powinienem zrobić w tej sytuacji?";
			link.l1.go = "Del_Deluck_5";
		break;
		
		case "Del_Deluck_5":
			dialog.text = "Użyj własnej głowy.";
			link.l1 = "To żeś mi pomógł...";
			link.l1.go = "Del_Deluck_6";
		break;
		
		case "Del_Deluck_6":
			DialogExit();
			AddQuestRecord("FolkeDeluc", "2");
			Return_TichingituOfficer();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
