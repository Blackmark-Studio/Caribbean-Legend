// диалоги обитателей плантаций
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, i, n;
	string sTemp;
	bool bOk;
	
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
			dialog.text = "Szükséged van valamire?";
			link.l1 = "Nem, nem kell.";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// рабы
		case "plantation_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Annyira fáradt vagyok, hogy máris összeesek...", "Nem élhetek így tovább!"), RandPhraseSimple("Ez a munka megöl engem.", "Az ôrök mindannyiunkat meg akarnak ölni!"));				
			link.l1 = RandPhraseSimple("Milyen kár.", "Sajnálom.");
			link.l1.go = "exit";				
		break;
		
		// рабы-пираты по пиратской линейке
		case "pirate_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Figyelj, menj el!", "Tûnj el!"), RandPhraseSimple("Mit akarsz?!", "Takarodj innen!"));				
			link.l1 = RandPhraseSimple("Hm...", "Nos...");
			link.l1.go = "exit";				
		break;
		
		// охрана - солдаты
		case "plantation_soldier":
            dialog.text = RandPhraseSimple(RandPhraseSimple("Menj, zavard az ültetvény vezetôjét", "Ne zavard a rabszolgákat, haver."), RandPhraseSimple("Az én dolgom, hogy motiváljam ezeket a lusta disznókat.", "Francba, túl meleg van ma, mint mindig..."));
			link.l1 = RandPhraseSimple("Értem...", "Valóban...");
			link.l1.go = "exit";
		break;
		
		// охрана - протектор
		case "plantation_protector":
            if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				if (sti(pchar.nation) == PIRATE)
				{
					PlaySound("Voice\English\soldier_arest_1.wav");
    				dialog.text = RandPhraseSimple("Kalóz?! Fogjátok el!", "Ô egy kalóz! Támadás!");
					link.l1 = RandPhraseSimple("Kalóz. És akkor mi van?", "Heh, csak rajta, próbáld meg.");
					link.l1.go = "fight"; 
					break;
				}
				PlaySound("Voice\English\soldier_arest_2.wav");
				dialog.text = RandPhraseSimple("Ho-ho, a "+NationNameGenitive(sti(pchar.nation))+"zászlaja alatt hajózol ! Szerintem a parancsnokunk szívesen beszélget veled!", "Hát-hát itt aztán büdös van "+NationNameAblative(sti(pchar.nation))+" ! Egy kém?! Itt az ideje, hogy beszéljen a parancsnokunkkal.");
				link.l1 = RandPhraseSimple("Elôször is, elküldelek a pokolba!", "Itt az ideje, hogy beszélj a pengémmel!");
				link.l1.go = "fight"; 
			}
			else
			{
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					if (sti(pchar.nation) == PIRATE)
					{
						PlaySound("Voice\English\soldier_arest_1.wav");
						dialog.text = RandPhraseSimple("Kalóz?! Fogjátok el!", "Ô egy kalóz! Támadás!");
						link.l1 = RandPhraseSimple("Kalóz!? Hol?", "Heh, csak rajta, próbáld meg.");
						link.l1.go = "fight"; 
						break;
					}
					PlaySound("Voice\English\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple("Ki vagy te és mit akarsz itt?", "Állj! Mi dolgod van itt?");
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Látni akarom a hely vezetôjét, hogy megbeszéljük az üzletet. Van kereskedelmi engedélyem.";
						link.l1.go = "Licence";
					}
					else
					{
						link.l1 = "Azért jöttem, hogy megbeszéljük az üzletet.";
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50))) link.l1.go = "PegYou";
						else link.l1.go = "NotPegYou";
					}
					if (IsCharacterPerkOn(pchar, "Trustworthy"))
					{
						link.l2 = "(Megbízható) Tisztelt szenátorok, a tisztességes és kölcsönösen elônyös kereskedelemért vagyok itt. Kérem, engedjenek az ültetvénytulajdonoshoz.";
						link.l2.go = "mtraxx_soldier_1";
						Notification_Perk(true, "Trustworthy");
					}
				}
				else
				{
					PlaySound("Voice\English\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple("Ki vagy te és mit akarsz itt?", "Állj! Mi dolgod van itt?");
					link.l1 = "Azért jöttem, hogy megbeszéljük az üzletet.";
					link.l1.go = "NotPegYou";
				}
			}
		break;
		
		case "Licence":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				PlaySound("Voice\English\soldier_arest_2.wav");
				dialog.text = "Engedélyt? Várjon egy pillanatot... Ha-ha, ez vicces! Tudom, hogy ki maga. Köröznek, haver! És a fejedért nagyon nagy jutalom jár! Fogjátok el!";
				link.l1 = RandPhraseSimple("Nos, ebben az esetben csak találkoznod kell a pengémmel!", "Cseszd meg.");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == -1)
			{
				PlaySound("Voice\English\soldier_arest_1.wav");
				dialog.text = "Lássuk csak... ha! A jogosítványod lejárt. Úgyhogy kövessetek, elviszlek titeket a parancsnokhoz...";
				link.l1 = RandPhraseSimple("A francba! Azt hiszem, itt az ideje, hogy találkozz a pengémmel, haver.", "Nem hinném...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			dialog.text = "Jól van. Bejöhetsz. Viselkedj és ne zavard a rabszolgákat.";
			link.l1 = "Ne aggódj, barátom.";
			link.l1.go = "plantation_exit";
		break;
		
		case "PegYou":
			PlaySound("Voice\English\soldier_arest_2.wav");
            dialog.text = "Üzleti? Ha-ha! Hát ez vicces! Ezer mérföldrôl bûzlesz a "+NationNameAblative(sti(GetBaseHeroNation()))+" szagától! Itt az ideje, hogy megismerkedj a parancsnokunkkal.";
			link.l1 = "Nem, azt hiszem, itt az ideje, hogy találkozz a pengémmel.";
			link.l1.go = "fight";
		break;
		
		case "NotPegYou":
            dialog.text = "Jól van. Bejöhetsz. Viselkedj és ne zavard a rabszolgákat.";
			link.l1 = "Ne aggódj, barátom.";
			link.l1.go = "plantation_exit";
		break;
		
		case "plantation_exit":
           DialogExit();
		   NextDiag.CurrentNode = "plantation_repeat";
		break;
		
		case "plantation_repeat":
            dialog.text = "Gyerünk, mozgás!";
			link.l1 = "...";
			link.l1.go = "plantation_exit";
		break;
		
		// управляющий в Маракайбо // Addon 2016-1 Jason
		case "Plantator":
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_2") // belamour legendary edition 
			{
				dialog.text = "Mi dolga van itt, senor?";
				link.l1 = TimeGreeting()+", senor. Van egy üzleti ajánlatom az Ön számára. Rabszolgákat szeretnék eladni. "+FindRussianQtyString(sti(GetSquadronGoods(pchar, GOOD_SLAVES)))+". Érdekli?";
				link.l1.go = "mtraxx";
				break;
			}
            dialog.text = "Mi dolga van itt, senor?";
			link.l1 = "Csak sétálgattam, csak köszönni akartam.";
			link.l1.go = "plantator_x";
		break;
		
		case "plantator_x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator";
		break;
		
		case "plantator_1":
			bOk = GetSquadronGoods(pchar, GOOD_COFFEE) >= 500 || GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500 || GetSquadronGoods(pchar, GOOD_COPRA) >= 500;
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup") && bOk) //пробуем выкупить Красавчика
			{
				dialog.text = "Már megint maga, senor. Hogy van?";
				link.l1 = "Van egy üzleti ajánlatom az ön számára. Cukrot és kakaót termel. Szeretném megvásárolni az áruját, de nem pénzért, hanem a saját árumat tudom felajánlani cserébe. Talán köthetnénk egy üzletet?";
				link.l1.go = "mtraxx_5";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_6" && bOk)
			{
				dialog.text = "Már megint maga, senor. Hogy van?";
				link.l1 = "Van egy üzleti ajánlatom az ön számára. Cukrot és kakaót termel. Szeretném megvásárolni az áruját, de nem pénzért, hanem a saját árumat tudom felajánlani cserébe. Talán köthetnénk egy üzletet?";
				link.l1.go = "mtraxx_5";
				break;
			}
            dialog.text = "Már megint maga, senor. Hogy van?";
			link.l1 = "Köszönöm, jól vagyok.";
			link.l1.go = "plantator_1x";
		break;
		
		case "plantator_1x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator_1";
		break;
		
		case "mtraxx":
			// belamour legendary edition возможность обмануть плантатора -->
			if(GetSquadronGoods(pchar, GOOD_SLAVES) >= 50 || CheckCharacterPerk(pchar, "Trustworthy") || ChangeCharacterHunterScore(Pchar, "spahunter", 0) <= -50)
			{
            dialog.text = "Csalódást kell okoznom, senor, de jelenleg nincs szükségünk rabszolgákra. Eduardo de Losada kapitány már ellátott minket kalózokkal, akiket a legutóbbi portyáján fogott el.";
			link.l1 = "Kalózok itt? Hogy tudtok itt egyáltalán aludni?";
			link.l1.go = "mtraxx_1";
			}
			else
			{
				dialog.text = "Ah, akkor lássuk csak... Megveszem a rabszolgáitokat. Nekem úgy tûnik, hogy nem az vagy, akinek mondod magad. Jöjjön velem a parancsnokságra, kedvesem, és ha tévedek, teljes mértékben fedezem az erkölcsi költségeit. És most elnézését kérem. Ôrség!";
				link.l1 = RandPhraseSimple("Álmodj csak, élve nem adom fel magam,Holtomiglan sem adom fel magam!”, “!");
				link.l1.go = "mtraxx_fail";
			}
		break;
		
		case "mtraxx_fail":
            DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddQuestRecord("Roger_3", "27");
			sld = characterFromId("Mtr_plantation_boss");
			sld.lifeday = 0;
			Mtraxx_PlantPellyClear();
			Mtraxx_TerraxReset(3);
		break;
		// <-- legendary edition
		case "mtraxx_1":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(characterFromId("Fadey"));
            dialog.text = "Jó ôrségünk van, így a lázadás esélye kicsi. De egy dologban igazad van: ezek a fattyúk szörnyû munkások. Nem vettem volna meg ôket, ha a kormányzó nem kéri, hogy tiszteljem don de Losadát. Ráadásul nem is kért értük sokat.";
			link.l1 = "Értem. Akkor el kell vitorláznom Los-Teques-be... Senor, körbejárhatom az ültetvényét és felfedezhetem? Talán szeretnék vásárolni a termésébôl...";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Ön kereskedô?";
			link.l1 = "Bizonyos fokig igen. Nem vagyok hivatásos kereskedô, de egy ígéretes üzletet sosem hagynék ki.";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Érdekes. Rendben, megkapja az engedélyemet. Jöjjön vissza, ha van valami ötlete.";
			link.l1 = "Köszönöm, senor. Azt hiszem, megteszem.";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   NextDiag.CurrentNode = "plantator_1";
		   pchar.questTemp.Mtraxx = "plant_3";
		   AddQuestRecord("Roger_3", "5");
		   Mtraxx_PlantSetMaxRocur();
		break;
		
		case "mtraxx_5":
            dialog.text = "Miért is ne? Milyen árut kínál?";
			if (GetSquadronGoods(pchar, GOOD_COFFEE) >= 500)
			{
				link.l1 = "500 láda kávé.";
				link.l1.go = "mtraxx_coffee";
			}
			if (GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500)
			{
				link.l2 = "500 doboz vaníliát.";
				link.l2.go = "mtraxx_cinnamon";
			}
			if (GetSquadronGoods(pchar, GOOD_COPRA) >= 500)
			{
				link.l3 = "500 doboz koprát.";
				link.l3.go = "mtraxx_copra";
			}
		break;
		
		case "mtraxx_coffee":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 11;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
            dialog.text = "Ötszáz doboz kávé? Nos, nos, nos... Lássuk csak... (számolva) kész vagyok elcserélni a kávéját "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" zsák cukorért és "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  doboz kakaóért. Megegyeztünk?";
			link.l1 = "Hmm... Jobb feltételekben reménykedtem. Nos, kit érdekel. Megegyeztünk!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(megbízható) Tisztelt uram, engedje meg, hogy tiltakozzam! A legjobb minôségû árut hoztam önnek. Ismerem minden egyes egység értékét, mind az általam kínált, mind az önök által cserébe kínált árut. Kicsit nagyobb rakományt érdemlek az önök részérôl, és ez az üzlet még mindig nyereséges lesz önöknek - ezt önök is nagyon jól tudják.";
				link.l1.go = "mtraxx_PlantVykup_2";
				Notification_Perk(true, "Trustworthy");
			}
		break;
		
		case "mtraxx_cinnamon":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 19;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 106;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 106;
            dialog.text = "Ötszáz doboz vanília? Nos, nos, nos... Lássuk csak... (számolva) kész vagyok elcserélni a vaníliát "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" zsák cukorért és "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  doboz kakaóért. Megegyeztünk?";
			link.l1 = "Hmm... Jobb feltételekben reménykedtem. Nos, kit érdekel. Megegyeztünk!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(megbízható) Tisztelt uram, engedje meg, hogy tiltakozzam! A legjobb minôségû árut hoztam önnek. Ismerem minden egyes egység értékét, mind az általam kínált, mind az önök által cserébe kínált árut. Kicsit nagyobb rakományt érdemlek az önök részérôl, és ez az üzlet még mindig nyereséges lesz önöknek - ezt önök is nagyon jól tudják.";
				link.l1.go = "mtraxx_PlantVykup_2";
				Notification_Perk(true, "Trustworthy");
			}
		break;
		
		case "mtraxx_copra":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 20;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
            dialog.text = "Ötszáz láda kopra? Nos, nos, nos... Lássuk csak...(számolom) kész vagyok elcserélni a kopráját "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" zsák cukorért és "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  doboz kakaóért. Megegyeztünk?";
			link.l1 = "Hmm... Reméltem jobb feltételeket... Hát, kit érdekel. Megegyeztünk!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(megbízható) Tisztelt uram, engedje meg, hogy tiltakozzam! A legjobb minôségû árut hoztam önnek. Ismerem minden egyes egység értékét, mind az általam kínált, mind az önök által cserébe kínált árut. Kicsit nagyobb rakományt érdemlek az önök részérôl, és ez az üzlet még mindig nyereséges lesz önöknek - ezt önök is nagyon jól tudják.";
				link.l1.go = "mtraxx_PlantVykup_2";
				Notification_Perk(true, "Trustworthy");
			}
		break;
		
		case "mtraxx_6":
            dialog.text = "Pompás! Mindkettônk számára jövedelmezô üzlet! Mikor fogjuk végrehajtani a cserét?";
			link.l1 = "Elôbb elô kell készítenem az árut. Neked is, azt hiszem. Kezdjük meg a cserét holnap este négy órakor. Az embereim napnyugta elôtt leszállítják a ládákat.";
			link.l1.go = "mtraxx_7";
		break;
		
		
		case "mtraxx_7":
            dialog.text = "Megegyeztünk. Akkor holnap találkozunk, senor!";
			link.l1 = "Viszlát...";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			AddQuestRecord("Roger_3", "10");
			pchar.questTemp.Mtraxx = "plant_7";
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.mtraxx_plant_goods.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtraxx_plant_goods.win_condition.l1.location = pchar.location;
			pchar.quest.mtraxx_plant_goods.function = "Mtraxx_PlantFindRocurDay";
		break;
		
		case "mtraxx_9":
            dialog.text = "Ez az, senor. Ha valaha is szüksége lesz cukorra vagy kakaóra, kérem, jöjjön el hozzám. Bármikor!";
			link.l1 = "Ha ez az alku kifizetôdônek bizonyul - még találkozunk. Most mennem kell, senor.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_10":
            dialog.text = "Viszlát, senor!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantAfterTrading");
		break;
		
		case "mtraxx_soldier_1":
            dialog.text = "Nem úgy néz ki, mint egy kereskedô, idegen. Mutassa az engedélyét.";
			link.l1 = "Kíméljen meg! Valami papír dönti el, hogy valaki kereskedhet-e vagy sem? Túl drágák! Csak nemrég kezdtem el kereskedni, de máris a szenvedélyemmé vált! Engedjen át, és majd szólok egy jó szót rólatok a tulajdonosnak.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_soldier_2":
            dialog.text = "Ezüst nyelved van, te nyomorult. Rendben, menj csak. De ne felejtsétek el megmondani a fônöknek, hogy mi ajánlottunk titeket neki.";
			link.l1 = "Hogyne. Köszönöm. Köszönöm.";
			link.l1.go = "plantation_exit";
		break;
		
		case "mtraxx_PlantVykup_2":
            dialog.text = "Maga jól ismeri az aktuális árakat, kapitány! Egyértelmûen ért az alkudozáshoz, még ha kezdônek is tûnik. Rendben, ha az áru valóban elsô osztályú, akkor azt hiszem, egy kis pluszt kell adnom önnek.";
			link.l1 = "Természetesen, elsô osztályú, esküszöm! Még egy dolog, uram. Szeretnék vásárolni önöktôl valamit.";
			link.l1.go = "mtraxx_PlantVykup_3";
		break;
		
		case "mtraxx_PlantVykup_3":
            dialog.text = "Ó? És mi lenne az?";
			link.l1 = "Valakit, nem valamit. Szeretném megvenni az egyik rabszolgáját, mint személyes szolgát. Ez lehetséges?";
			link.l1.go = "mtraxx_PlantVykup_4";
		break;
		
		case "mtraxx_PlantVykup_4":
            dialog.text = "Nem probléma. Megtaláljuk a megfelelôt.";
			link.l1 = "Egy bizonyos rabszolga érdekelne. Akinek elbûvölô arca van - akit nem szégyellne hivatalos eseményekre vinni, vagy borral kínálni a vendégeket. Jean Picardként mutatkozott be. Már megismerkedtünk.";
			link.l1.go = "mtraxx_PlantVykup_5";
		break;
		
		case "mtraxx_PlantVykup_5":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 70)
			{
				dialog.text = "Igen, van kereslet Jean Picardra - nem csak a bor felszolgálásában. Egy befolyásos angol már felvette velem a kapcsolatot. Egy férfi, hogy is hívják... Pattornson? Átadott nekem egy levelet.";
				link.l1 = "De sem Pattornson, sem az ügyfele nem jelentkezett még. Kész vagyok megvenni Jean-t magától itt és most. Nevezze meg az árát - a hölgyek várnak!";
				link.l1.go = "mtraxx_PlantVykup_10";
				Notification_Skill(true, 70, SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Á, jól kijöttek. Megértem. De attól tartok, vissza kell utasítanom - Jean Picard nem eladó. Sajnálom, senor.";
				link.l1 = "Ó? Miért is? Hajlandó vagyok bôségesen fizetni. Csak mondja meg az árat.";
				link.l1.go = "mtraxx_PlantVykup_6";
				Notification_Skill(false, 70, SKILL_COMMERCE);
			}
		break;
		
		case "mtraxx_PlantVykup_6":
            dialog.text = "B-ártalan. Már van vevôje. Másnak ígértem. Nincs több mondanivalóm. Térjünk vissza az eredeti üzlethez és fejezzük be a kereskedést.";
			link.l1 = "Hmm, ahogy kívánja, senor.";
			link.l1.go = "mtraxx_PlantVykup_7";
		break;
		
		case "mtraxx_PlantVykup_7":
            dialog.text = "Pompás! Mindkettônk számára jövedelmezô üzlet! Mikor fogjuk végrehajtani a cserét?";
			link.l1 = "Elôbb elô kell készítenem az árut. Neked is, azt hiszem. Kezdjük meg a cserét holnap este négy órakor. Az embereim napnyugta elôtt leszállítják a ládákat.";
			link.l1.go = "mtraxx_PlantVykup_8";
		break;
		
		
		case "mtraxx_PlantVykup_8":
            dialog.text = "Megegyeztünk. Akkor holnap találkozunk, senor!";
			link.l1 = "Viszlát...";
			link.l1.go = "mtraxx_PlantVykup_9";
		break;
		
		case "mtraxx_PlantVykup_9":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			pchar.questTemp.mtraxx_PlantVykup2 = true;
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
			DoFunctionReloadToLocation("Shore37", "goto", "goto6", "Mtraxx_PlantPlantVykup_1");
		break;
		
		case "mtraxx_PlantVykup_10":
            dialog.text = "Ahogy óhajtja, senor. De értse meg, az ár borsos: ötszáz dublon.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Ez nem probléma - tessék. Egy jó személyi szolga többet ér, mint egy közönséges rabszolga, mint azt jól tudod.";
				link.l1.go = "mtraxx_PlantVykup_11";
			}
			else
			{
				link.l2 = "Elég magas árat szabott, uram. De engem nagyon érdekel ez a rabszolga. Várjon itt. Ha Pattornson megjelenik, mondja meg neki, hogy Picardot már eladták - ha-ha-ha-ha!";
				link.l2.go = "mtraxx_PlantVykup_13";
			}
		break;
		
		case "mtraxx_PlantVykup_11":
            dialog.text = "Igaza van. Majd én intézkedem. Picard odakint fog várni rád.";
			link.l1 = "...";
			link.l1.go = "mtraxx_PlantVykup_12";
			RemoveDublonsFromPCharTotal(500);
		break;
		
		case "mtraxx_PlantVykup_12":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			pchar.questTemp.mtraxx_PlantVykup3 = true;
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
			DoFunctionReloadToLocation("Maracaibo_ExitTown", "rld", "loc17", "Mtraxx_PlantPlantVykup_2");
		break;
		
		case "mtraxx_PlantVykup_13":
            dialog.text = "Ha a teljes összeggel jön, kétlem, hogy elküldeném. Úgyhogy siessen, kapitány.";
			link.l1 = "Hamarosan visszajövök.";
			link.l1.go = "mtraxx_PlantVykup_14";
		break;
		
		case "mtraxx_PlantVykup_14":
            DialogExit();
			NextDiag.CurrentNode = "mtraxx_PlantVykup_15";
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
		break;
		
		case "mtraxx_PlantVykup_15":
            dialog.text = "Elhozta az aranyat Jean Picardnak, kapitány? Az idô sürget.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Tisztában vagyok vele. Tessék, vigye az aranyat, és adja át az új háziszolgámat.";
				link.l1.go = "mtraxx_PlantVykup_16";
			}
			else
			{
				link.l2 = "Még mindig gyûjtögetem - maga az, aki ilyen magas árat szabott meg, senor.";
				link.l2.go = "mtraxx_PlantVykup_14";
			}
		break;
		
		case "mtraxx_PlantVykup_16":
            dialog.text = "Soha nem láttam még senkit, aki ennyit költött volna egy szolga megszerzésére. De abból ítélve, hogy milyen jól öltözött, bizonyára hozzászokott az ilyen nagyszabású vásárlásokhoz. Értesítem az embereimet, Picard pedig a kijáratnál várja önt.";
			link.l1 = "...";
			link.l1.go = "mtraxx_PlantVykup_12";
			RemoveDublonsFromPCharTotal(500);
		break;
	}
} 
