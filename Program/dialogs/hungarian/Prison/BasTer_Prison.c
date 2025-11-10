// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Beszéljen, hallgatom.";
			link.l1 = "Tévedtem. Viszontlátásra.";
			link.l1.go = "Exit";
			// --> Тичингиту
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "true")
            {
                link.l1 = "Egy indiánt letartóztattak. Fadey, a moszkovita fogta el. Beszélhetek vele?";
                link.l1.go = "Tichingitu";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "commandante")
            {
                link.l1 = "Mondd, tényleg fel akarod akasztani ezt az indiánt? Nem túl kemény büntetés ez egy ilyen kis bûnért?";
                link.l1.go = "Tichingitu_3";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "pay")
            {
                link.l1 = "Megint én vagyok az, parancsnok. Fadey, a moszkovita írta ezt a kérvényt, hogy engedjék szabadon az indiánt. Itt van.";
                link.l1.go = "Tichingitu_6";
            }
			// <-- Тичингиту
			//Jason --> Бесчестный конкурент
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l1 = "A helyi bolt tulajdonosának kérésére jöttem önökhöz, a neve "+pchar.questTemp.Shadowtrader.Tradername+". Ô kért meg, hogy adjam át ezt a levelet.";
				link.l1.go = "Shadowtrader_prison";
			}
			
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.SeekTrader") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l1 = "Ez megint én vagyok. Alapos bizonyítékom van arra, hogy a "+pchar.questTemp.Shadowtrader.Tradername+" igaza van.";
				link.l1.go = "Shadowtrader_prison2";
			}
			//Jason <-- Бесчестный конкурент
			//Sinistra --> Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerTurma"))
            {
                link.l1 = "Egy Longway nevû embert keresek. Hallom, ön is ôt keresi, Monsieur Officer. Volt már szerencséje megtalálni ôt, vagy esetleg valami nyom?";
                link.l1.go = "PZ_IshemLongway_1";
            }
			//Sinistra <-- Путеводная звезда
		break;
		
		// --> Тичингиту
		case "Tichingitu":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
			dialog.text = "Fadey elmesélte a történetét? Nincs okom megtiltani, hogy megnézze ôt, monsieur. Nem ön az elsô, aki meglátogatja azt a vörösbôrt. Nos, tíz nap múlva minden polgár megnézheti, amikor a napon száradni fog...";
			link.l1 = "Szóval, bemehetek a börtönbe?";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Ahogy már mondtam neked 'Nincs okom megtiltani ezt neked'. Menj tovább.";
			link.l1 = "Köszönjük!";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "Tichingitu_3":
			DelLandQuestMark(npchar);
			dialog.text = "Ön új itt, ugye, uram? Európából jött? Nem érti a helyzetet a gyarmatokon. Ez a kivégzés lecke lesz azoknak a rézbôrû fattyúknak, akik a francia gyarmatosítók tulajdonába merészkednek. Különben is, maga Fadey ragaszkodik ehhez, és ô egy nagyon tisztelt ember itt, és a kormányzó közeli barátja.";
			link.l1 = "Van rá mód, hogy enyhítsük a büntetést? Még mindig úgy gondolom, hogy túl szigorú...";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Ó, ne menjünk bele a filozófiába! Menjen el Fadeyhez, és kérje ezt az indiánt, ha tényleg ennyire érdekli a sorsa. Ha Fadey ír egy petíciót a szabadon bocsátásáért, mi teljesíteni fogjuk.";
			link.l1 = "Értettem, tiszt úr. Elmegyek Fadeyhez.";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "fadey";
			AddLandQuestMark(characterFromId("fadey"), "questmarkmain");
			QuestPointerToLoc("BasTer_town", "reload", "houseSp1");
		break;
		
		case "Tichingitu_6":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
			RemoveItems(pchar, "letter_1", 1);
			dialog.text = "(olvasás) Hm... Ez a Fadey furcsa... Elôbb demonstratív kivégzést követelt, most meg azt kéri, hogy engedjék szabadon ezt az indiait... Mindegy, gondolom a kormányzó minden barátja ilyen. Rendben, menjetek és vigyétek ezt a rézbôrût.";
			link.l1 = "Köszönöm, tiszt úr!";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			AddQuestRecord("Tichingitu", "3");
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_6";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		// <-- Тичингиту
		
		//Jason --> мини-квест Бесчестный конкурент
		case "Shadowtrader_prison":
			dialog.text = "Megint az a "+pchar.questTemp.Shadowtrader.Tradername+" a panaszaival! Rendben, lássuk, hogy ezúttal mi az... (végigolvas)";
			link.l1 = "...";
			link.l1.go = "Shadowtrader_prison_1";
			RemoveItems(PChar, "letter_1", 1);
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Fort");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_prison_1":
			dialog.text = "Ismét abszurd találgatások és egyetlen erôs bizonyíték sincs! Rendben. Mondd meg neki, hogy ez egyszerûen nem elég ahhoz, hogy riadóztassam az ôrséget, és utasítsam ôket, hogy fésüljék át a várost.";
			link.l1 = "Azt akarod, hogy ezt mondjam neki?";
			link.l1.go = "Shadowtrader_prison_2";
		break;
		
		case "Shadowtrader_prison_2":
			dialog.text = "Pontosan - és lehetôleg szóról szóra. Meg fogja érteni, mire gondolok. Nem pazarolom a papírt arra, hogy választ írjak erre az idegesítôre.";
			link.l1 = "Értem. Akkor viszlát.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.Trouble = "true";
			NextDiag.TempNode = "First_officer";
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
		
		case "Shadowtrader_prison2":
			dialog.text = "És mi ez a 'megalapozott' bizonyíték, amit állítólag összegyûjtött?";
			link.l1 = "Megállapodtam a csempészekkel a nem hivatalos boltjukon keresztül történô áruvásárlásról. Az ügynökük ma este eljön a kikötôi hatóság irodájába, hogy elvigyen az úgynevezett 'boltjukba'..";
			link.l1.go = "Shadowtrader_prison2_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
			pchar.quest.ShadowtraderTimeSmugglers_Over.over = "yes";
			pchar.quest.Shadowtrader_SMG.over = "yes";//снять оба прерывания
			sld = characterFromID("ShadowAgent_1");
			sld.lifeday = 0;
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_prison2_1":
			dialog.text = "Hhm... Nos, kiváló munka, kapitány! Akkor majd mi tovább cselekszünk. Elküldjük az emberünket a találkozójukra, felkutatjuk a rejtekhelyüket és letartóztatjuk mindannyiukat. Köszönjük a kezdeményezést!";
			link.l1 = "Mindig örömmel segítek. Biztos vagyok benne, hogy a mûvelet sikeres lesz.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.End.Fort = "true";
			AddQuestRecord("Shadowtrader", "7");
			AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase("","а"));
			SetTimerFunction("ShadowTrader_questmark", 0, 0, 1);
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			NextDiag.TempNode = "First_officer";
		break;
		// <-- мини-квест Бесчестный конкурент
		
		// Sinistra - Квест "Путеводная звезда" ==>
		case "PZ_IshemLongway_1":
			DelLandQuestMark(npchar);
			dialog.text = "Ki az? Hosszú... Hosszú... Nem emlékszem, hogy angolok jártak volna mostanában a városunkban.";
			link.l1 = "Nem, Longway... kínai.";
			link.l1.go = "PZ_IshemLongway_2";
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTurma");
			DeleteQuestCondition("PZ_BasTerPeshera");
		break;
		
		case "PZ_IshemLongway_2":
			dialog.text = "Nocsak, nocsak. És miért keresi ezt a Longwayt, monsieur?";
			link.l1 = "Ô az egyik barátom. Már hallottam, hogy mi történt - ez egy szomorú félreértés, biztosíthatom.";
			link.l1.go = "PZ_IshemLongway_Zashita_1";
			if (pchar.location.from_sea != "BasTer_Town")
			{
				link.l2 = "Azért keresem, mert ô egy ismert bûnözô a szigetvilágban.";
				link.l2.go = "PZ_IshemLongway_OhotnikOtryad_1";
			}
		break;
		
		case "PZ_IshemLongway_Zashita_1":
			dialog.text = "Ah, egy félreértés. Nem akartuk helyben helyrehozni, ha másért nem, hát azért. Csak beszélni akartunk vele... kezdetnek. Azonban ez az önök agresszív sárga embere nem csak több városôrséget vágott le, hanem lemészárolta az üldözésére küldött egységeket is a dzsungelben.";
			link.l1 = "Terveztek még egy egységet küldeni? Elmehetnék az embereiddel, beszélhetnék vele, megnyugtathatnám, és megelôzhetnék egy újabb katasztrófát. Elég lenne, ha a gyilkosságok abbamaradnának, és Longway végleg elhagyná a várost?";
			link.l1.go = "PZ_IshemLongway_Zashita_2";
		break;
		
		case "PZ_IshemLongway_Zashita_2":
			dialog.text = "Normális körülmények között egyetértenék magával. De tudja, a megöltek egyike egy tiszt volt - egy ígéretes fiatal hadnagy, Ôkegyelmessége kedvence. A város gyászol. Nem lehet szemet hunyni felette, vagy kárpótolni. Megértette?";
			link.l1 = "Tökéletesen megértem. Bocsánatot kérek a barátom tetteiért. Nem zavarom tovább.";
			link.l1.go = "PZ_IshemLongway_Uiti_1";
			link.l2 = "Tudja, csak Isten tudja, mi folyik a dzsungelben. Bárki megölhette volna azokat az embereket.";
			link.l2.go = "PZ_IshemLongway_Blef_1";
		break;
		
		case "PZ_IshemLongway_Blef_1":
			dialog.text = "És mit gondol, ki tudott volna leteríteni egy egész járôrcsapatot egy tiszt vezetésével?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l1 = "(megbízható) Banditák, ki más? Szégyellem bevallani, de nemrég épphogy megúsztam egy hatalmas bandát.";
				link.l1.go = "PZ_IshemLongway_Blef_2";
			}
			else
			{
				Notification_Perk(false, "Trustworthy");
				link.l1 = "De honnan tudnám? Bárki lehetett volna - rablók, kalózok, kémek...";
				link.l1.go = "PZ_IshemLongway_Blef_netVD_1";
			}
		break;
		
		case "PZ_IshemLongway_Blef_2":
			dialog.text = "Heh, ez nem meglepô - figyelembe véve a testméretét, kapitány. Igen, vannak ilyen gazemberek a szigeten manapság...";
			link.l1 = "Pontosan! Szóval, lemészárolhatták volna az ôrjáratot és a szegény alhadnagyot.";
			link.l1.go = "PZ_IshemLongway_Blef_3";
		break;
		
		case "PZ_IshemLongway_Blef_3":
			dialog.text = "Sajnos, ez teljesen lehetséges.";
			link.l1 = "Pontosan. Ezért még egyszer kérem, engedje meg, hogy csatlakozhassak a következô keresôcsapathoz - Longway hallgatni fog rám, és így elkerülhetjük a további haláleseteket.";
			link.l1.go = "PZ_IshemLongway_Blef_4";
		break;
		
		case "PZ_IshemLongway_Blef_4":
			dialog.text = "Rendben. De van még egy 'de,' uram.";
			link.l1 = "És mi lenne az?";
			link.l1.go = "PZ_IshemLongway_Blef_5";
		break;
		
		case "PZ_IshemLongway_Blef_5":
			dialog.text = "A dzsungelben történtekkel ellentétben a barátod bûnössége a városban egyértelmû és teljesen bizonyított. Nem marad büntetlenül. Tehát ezeket a haláleseteket kompenzálni kell, ha azt akarod, hogy élve hagyja el a várost.";
			link.l1 = "Elég tisztességes. Mennyibe fog ez kerülni, tiszt úr?";
			link.l1.go = "PZ_IshemLongway_Blef_6";
		break;
		
		case "PZ_IshemLongway_Blef_6":
			dialog.text = "Háromszáz dublont. Ezt a pénzt a város kapja, nem pedig a piactéri harcosok.";
			if (PCharDublonsTotal() >= 300)
			{
				link.l1 = "Hát persze. Háromszáz dublon - tessék.";
				link.l1.go = "PZ_IshemLongway_Blef_7";
			}
			link.l2 = "Ezúttal nem hoztam be a városba a dublonjaimat. De ha megengeded, hogy visszaszerezzem ôket...";
			link.l2.go = "PZ_IshemLongway_NetDublonov_1";
		break;
		
		case "PZ_IshemLongway_Blef_7":
			dialog.text = "Remek. Bizonyítottad a felelôsségtudatodat. Épp most fejezzük be a következô osztag eligazítását. Engedélyezem, hogy csatlakozz hozzá.";
			link.l1 = "Köszönöm, uram. Viszlát, tiszt úr.";
			link.l1.go = "PZ_IshemLongway_BeryomOtryad";
			RemoveDublonsFromPCharTotal(300);
			pchar.questTemp.PZ_DrugOtryad = true;
		break;
		
		case "PZ_IshemLongway_NetDublonov_1":
			dialog.text = "Nem tegnap születtem. Tudom, hogy el akar szökni - nem a dublónokért, hanem a kedves kínaiért.";
			link.l1 = "A szavamat adom, hogy nem hagyom el a várost Longway-vel.";
			link.l1.go = "PZ_IshemLongway_NetDublonov_2";
		break;
		
		case "PZ_IshemLongway_NetDublonov_2":
			dialog.text = "Szavak, szavak... Elegem van a fecsegésébôl, kapitány. Addig nem megy sehová, amíg mi magunk el nem kapjuk ezt az istenverte sárga bôrû embert.";
			link.l1 = "Engedelmeskedem a parancsának, ha megígéri, hogy nem öli meg Longwayt helyben, tiszt úr.";
			link.l1.go = "PZ_IshemLongway_Arest_1";
			link.l2 = "De vajon én személyesen sértettem meg ma a város törvényeit?";
			link.l2.go = "PZ_IshemLongway_Pobeg_1";
		break;
		
		case "PZ_IshemLongway_Blef_netVD_1":
			dialog.text = "Akkor nem tudja. Maradok a jelenlegi megérzésemnél - a kínait mindenképpen el kell kapni.";
			link.l1 = "A jelenlegi megérzésed? De nincs bizonyítékod arra, hogy Longway mindenkit megölt a dzsungelben.";
			link.l1.go = "PZ_IshemLongway_Blef_netVD_2";
		break;
		
		case "PZ_IshemLongway_Blef_netVD_2":
			dialog.text = "És van bizonyítéka az ártatlanságára? Nincs? Akkor ne csináljon szentet a sárga bôrû emberébôl. Megértette?";
			link.l1 = "Tökéletesen megértem. Bocsánatot kérek a barátom tetteiért. Nem zavarom tovább.";
			link.l1.go = "PZ_IshemLongway_Uiti_1";
		break;
		
		case "PZ_IshemLongway_Uiti_1":
			dialog.text = "Attól tartok, még nem engedhetem el, kapitány.";
			link.l1 = "Hogy érti ezt?";
			link.l1.go = "PZ_IshemLongway_Uiti_2";
		break;
		
		case "PZ_IshemLongway_Uiti_2":
			dialog.text = "Úgy értem, hogy mivel ez a Longway a barátod, nincs rá garancia, hogy nem futsz utána, és nem próbálsz meg vele együtt megszökni. Szóval, addig kell itt tartanom téged, amíg mi magunk el nem kapjuk ezt a sárga bôrû mészárost.";
			link.l1 = "Engedelmeskedem a parancsának, ha megígéri, hogy nem öli meg Longwayt helyben, tiszt úr.";
			link.l1.go = "PZ_IshemLongway_Arest_1";
			link.l2 = "De vajon én személyesen sértettem meg ma a város törvényeit?";
			link.l2.go = "PZ_IshemLongway_Pobeg_1";
		break;
		
		case "PZ_IshemLongway_Arest_1":
			dialog.text = "Nem ígérhetek semmit. Ki tudja, mit forgat a barátod a fejében, vagy hogy újabb mészárlásba kezd-e, ha meglát minket. Addig is, kérem, élvezze a luxusszállását, kapitány.";
			link.l1 = "Röhejes...";
			link.l1.go = "PZ_IshemLongway_Arest_2";
		break;
		
		case "PZ_IshemLongway_Arest_2":
			DialogExit();
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			bDisableCharacterMenu = true;
			InterfaceStates.Buttons.Save.enable = false;
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation("BasTer_prison", "goto", "goto9", "PZ_SharliePlennik_BadFinal");
		break;
		
		case "PZ_IshemLongway_Pobeg_1":
			dialog.text = "Értse meg, semmi bajom magával személyesen. És igaza van - nem követett el semmilyen bûncselekményt. De biztosítanunk kell, hogy a sárga bôrû barátja ne ússza meg az igazságszolgáltatást.";
			link.l1 = "Akkor értse meg, hogy nem fogom megengedni, hogy ilyen szemfényvesztô módon ôrizetbe vegyenek.";
			link.l1.go = "PZ_IshemLongway_Pobeg_2";
		break;
		
		case "PZ_IshemLongway_Pobeg_2":
			if (pchar.location.from_sea == "BasTer_Town")
			{
				dialog.text = "Ebben az esetben le kell csendesítenünk, uram.";
			}
			else
			{
				dialog.text = "Elegem van ebbôl! Ôrmester, vezesse az osztagot ahhoz az átkozott barlanghoz, és keressék meg a kínaiakat! Ezt személyesen intézem el...";
			}
			link.l1 = "A pokolba is.";
			link.l1.go = "PZ_IshemLongway_Pobeg_3";
		break;
		
		case "PZ_IshemLongway_Pobeg_3":
			DialogExit();
			
			LAi_SetHuberType(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_MoveCharacter(NPChar, "FRANCE_CITIZENS");
			LAi_group_Attack(characterFromId("BasTer_Mayor"), Pchar);
			ChangeCharacterNationReputation(pchar, FRANCE, -50);
			if (pchar.location.from_sea == "BasTer_Town")
			{
				PChar.quest.PZ_KorablPort_BadFinal.win_condition.l1 = "MapEnter";
				PChar.quest.PZ_KorablPort_BadFinal.win_condition = "PZ_KorablPort_BadFinal";
				AddQuestRecord("PZ", "10");
				LocatorReloadEnterDisable("BasTer_town", "gate_back", true);
				Island_SetReloadEnableGlobal("Guadeloupe", false);
			}
			else
			{
				PChar.quest.PZ_KorablBuhta_BadFinal.win_condition.l1 = "EnterToSea";
				PChar.quest.PZ_KorablBuhta_BadFinal.win_condition = "PZ_KorablBuhta_BadFinal";
				AddQuestRecord("PZ", "5");
				
				// Микро-диалог с Лонгвэем у пещеры, если мы побежали к пещере ему помочь после ссоры с комендантом
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1 = "location";
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1.location = "Guadeloupe_CaveEntrance";
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition = "PZ_IshemLongway_SorraKomendant";
				
				LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", true);
				LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", true);
				//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", true);
			}
		break;
		
		case "PZ_IshemLongway_OhotnikOtryad_1":
			dialog.text = "Fejvadász, mi? Általában nem szeretek a fajtáddal üzletelni, de ebben az esetben elônyömre válik, hogy az érdekeink egybeesnek. Úgy tûnik, ez a sárga bôrû egy hírhedt gyilkos. Sok emberemet megölte, a városban és a dzsungelben egyaránt.";
			link.l1 = "Már egy ideje üldözöm ôt az egész szigetvilágban.";
			link.l1.go = "PZ_IshemLongway_OhotnikOtryad_2";
		break;
		
		case "PZ_IshemLongway_OhotnikOtryad_2":
			dialog.text = "Átkozott gazember! A következôt fogjuk tenni: Összeszedek egy másik osztagot, és te velük mész. Ezúttal nincs hová menekülnie, és a segítségeddel nagyobb esélyünk lesz a sikerre. Viszont ne várj jutalmat tôlem - te fejvadász vagy, úgyhogy a fizetséged attól kapod, aki felbérelt téged. Hálásnak kellene lenned, hogy egyáltalán együttmûködhetsz velem.";
			link.l1 = "Ez így igaz. Viszlát késôbb, biztos úr. Ha bármelyik embere túlél egy újabb találkozást a kínai barátunkkal, majd szólok, hogy mi történt.";
			link.l1.go = "PZ_IshemLongway_BeryomOtryad";
			pchar.questTemp.PZ_OhotnikOtryad = true;
		break;
		
		case "PZ_IshemLongway_BeryomOtryad":
			DialogExit();
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", true);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", true);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", true);
			DoQuestReloadToLocation("Guadeloupe_jungle_02", "goto", "goto1", "PZ_IshemLongway_Otryad");
		break;
		
		case "PZ_BasTer_ComendantDialog_1":
			dialog.text = "Igaza van. Maguk ketten ismerôsök, ugye? Kik vagytok egymásnak?";
			link.l1 = " Ô egy navigációs tiszt a hajómon, és...";
			link.l1.go = "PZ_BasTer_ComendantDialog_2";
			if (pchar.location.from_sea != "BasTer_Town")
			{
				link.l2 = "Azért keresem, mert ô egy ismert bûnözô a szigetvilágban.";
				link.l2.go = "PZ_IshemLongway_OhotnikOtryad_1";
			}
		break;
		
		case "PZ_BasTer_ComendantDialog_2":
			dialog.text = "Jobban bánik a fegyverekkel, mint a térképekkel. Van fogalma arról, hogy mit tett a kínai háziállata?";
			link.l1 = "Hogy ôszinte legyek, nem, mert csak kikötöttem és elkezdtem keresni. Biztos vagyok benne, hogy az egész csak egy félreértés volt.";
			link.l1.go = "PZ_IshemLongway_Zashita_1";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_1":
			dialog.text = "Pontosan. Ki vagy te neki, ha ennyire akarod? Nem számít - ami fontos, az a városlátogatásod célja.";
			link.l1 = "Semmi illegális, uram. De mit értett azon, hogy “ez már nem számít”? Ô...";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_2";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_2":
			dialog.text = "Igen. Az egyik domb mögött temették el, a temetôtôl kissé távolabb. A szentatyák nem engedték meg, hogy egy pogánynak megfelelô keresztény temetést rendezzenek.";
			link.l1 = "Hogy történt, ha nem titok?";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_3";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_3":
			dialog.text = "Nagyon egyszerûen - érkezett a városba, vég nélkül szimatolva. Megpróbáltunk beszélni vele, hogy megtudjuk, mit keres itt, de megölt néhány embert, és elmenekült a dzsungelbe. Több keresôcsapatot küldtem utána, egyiket a másik után, de mindet eltörölte! Csapdába kellett csalnunk egy barlangban, a többit a mesterlövészek végezték el.";
			link.l1 = "És nem tudod, hogy mit keresett? Tudod, még soha nem csinált ilyesmit - korábban navigátor volt a hajómon. De aztán meglopott engem, és elszökött.";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_4";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_4":
			dialog.text = "Egyszerûen kiment a fejembôl, igen. Szóval, te is szenvedtél a tettei miatt? Ez majd megtanítja a leckére, kapitány. Tudni fogja, hogy nem szabad olyasvalakivel összeállni, akiben nem bízik. Soha ne bízz egy sárga bôrû emberben - jegyezd meg a szavaimat!";
			link.l1 = "Igen, ezt észben tartom. Találtál valamit nála?";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_5";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_5":
			dialog.text = "Ó, vissza akarja szerezni az ellopott árut? Volt némi ezüst a zsebében, szóval ha lopott is tôled, már elköltötte az egészet. És volt még néhány papír... a hajónaplójából? Amúgy sem értettük - talán valamiféle kód? Minden csupa vér volt, így nem tudtuk kivenni a sértetlen részeket.";
			link.l1 = "Igen, igen. Köszönöm, uram. Mindig is aggódtam, mi lenne, ha a naplóimat és a naplóimat valaki más venné fel...";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_6";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_6":
			dialog.text = "És hogy emiatt egy teljesen összetett rejtjelezést kell kitalálnom? Nem sajnáltad az idôdet és a fáradozásodat? Tessék, tessék. És az ezüstrôl - ne haragudj, de visszavittük a városba. Az a kínai sok emberemet a földbe döngölte aznap.";
			link.l1 = "Akkor nem merek ragaszkodni hozzá. Viszontlátásra.";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_7";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_7":
			DialogExit();
			
			LAi_SetHuberType(npchar);
			AddQuestRecord("PZ", "9");
			CloseQuestHeader("PZ");
			bDisableLandEncounters = false;
		break;
		// <== Квест "Путеводная звезда" - Sinistra
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
