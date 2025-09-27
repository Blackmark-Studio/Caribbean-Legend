// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdések?", "Mit akarsz, " + GetAddress_Form(NPChar) + "?"), "Már próbáltál kérdezni " + GetAddress_Form(NPChar) + "...", "Ma már harmadszor beszélsz valamilyen kérdésrôl...",
                          "Nézze, ha nincs mondanivalója a kikötô ügyeirôl, akkor ne zavarjon a kérdéseivel.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam.", "Nincs mirôl beszélnem."), "Nevermind.", "Valóban, már harmadszor...", "Sajnálom, de egyelôre nem érdekelnek a kikötô ügyei.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			// belamour legengary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet"))
			{
				if(pchar.questTemp.SharkGoldFleet == "toCarPortOffice" || pchar.questTemp.SharkGoldFleet == "start" || pchar.questTemp.SharkGoldFleet == "afterGvik" || pchar.questTemp.SharkGoldFleet == "buyincar")
				{
					link.l1 = "Az a helyzet, hogy bármelyik nap Porto Bellóba indulhatok egy rakomány áruval, amelyet önöktôl vásároltam a gyarmaton. Arra gondoltam: talán van valamilyen szállítmánya vagy üzlete, amit útközben elintézhetek ... Természetesen díj ellenében.";
					link.l1.go = "SharkGoldFleet";
				}
				if(pchar.questTemp.SharkGoldFleet == "LightVar")
				{
					if(!bImCasual) pchar.quest.SharkGoldFleetToCPO10.over = "yes";
					link.l1 = "Üdvözlöm újra. Elvittem a levelét Porto Bellóba. Ott megkértek, hogy válaszoljak.";
					link.l1.go = "SharkGoldFleet_09";
				}
				if(pchar.questTemp.SharkGoldFleet == "DifficultVar")
				{
					if(!bImCasual) pchar.quest.SharkGoldFleetToCPO10.over = "yes";
					link.l1 = "Jó napot! Jó napot! Porto Bellóból jöttem önhöz. A helyi kikötôi hatóság munkatársa kért meg, hogy adjam át ezt a levelet.";
					link.l1.go = "SharkGoldFleet_13";
				}
			}
			//<-- на пару с Акулой
		break;
		
		// belamour на пару с Акулой -->
		case "SharkGoldFleet":
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet.Fail21"))
			{
				pchar.questTemp.SharkGoldFleet = "toCurierDie";
				AddQuestRecord("SharkGoldFleet", "5");
				SGF_CreateCurierInWorld("");
				dialog.text = "Köszönöm az aggodalmát, de nincsenek ilyen ügyeim. Valójában volt egy megbízás, de Ön szó szerint néhány napot késett: Erre a célra egy nagy sebességû futárszállító luggert küldtem.";
				link.l1 = "Értettem... Hát, köszönöm szépen.";
				link.l1.go = "exit";
			}
			else
			{
				if(!bImCasual) pchar.quest.SharkGoldFleet21.over = "yes"; 
				if(!bImCasual) pchar.quest.SharkGoldFleet30.over = "yes"; 
				if(GetCompanionQuantity(pchar) > 1)
				{
					pchar.questTemp.SharkGoldFleet = "toCurierWait";
					AddQuestRecord("SharkGoldFleet", "10");
					SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
					dialog.text = "Látom, hogy még egy hajójuk sincs. Ön bizonyára gazdag kereskedô. Hmm ... De én látásból ismerem az összes helyi kereskedôt, akinek hajóhada van, de önt nem ismerem. Szóval ne hibáztass, de nem bízhatok rád semmi komolyat.";
					link.l1 = "Értettem... Hát, köszönöm szépen.";
					link.l1.go = "exit";
				}
				else
				{
					if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
					{
						pchar.questTemp.SharkGoldFleet = "toCurierWait";
						AddQuestRecord("SharkGoldFleet", "11");
						SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
						dialog.text = "Hmm... Van egy feladatom. Csak most a hajód nem illik bele. Olyan hajóra van szükségem, ami egyszerre gyors és erôs, és a tiéd nem felel meg teljesen ezeknek a követelményeknek. Legalábbis egyszerre. Szóval kérlek, bocsáss meg nekem.";
						link.l1 = "Értettem... Hát, köszönöm szépen.";
						link.l1.go = "exit";
					}
					else
					{
						if(!CheckAttribute(pchar,"questTemp.SharkGoldFleet.LicenceOk"))
						{
							pchar.questTemp.SharkGoldFleet = "toCurierWait";
							AddQuestRecord("SharkGoldFleet", "12");
							SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
							dialog.text = "Van egy kis dolgom... És neked jó hajód van. Csak nem úgy néz ki, mint egy kereskedô. És amennyire én látom, nincs hosszú távú engedélye a Holland Nyugat-indiai Társaságtól. Ne vegye sértésnek, de nem úgy néz ki, mint egy kereskedô. Nem vállalhatom ezt a kockázatot.";
							link.l1 = "Értettem... Hát, köszönöm szépen.";
							link.l1.go = "exit";
						}
						else
						{
							if(pchar.questTemp.SharkGoldFleet != "toCarPortOffice" || GetSquadronGoods(pchar, GOOD_COFFEE) < 300 || GetSquadronGoods(pchar, GOOD_CHOCOLATE) < 300)
							{
								pchar.questTemp.SharkGoldFleet = "toCurierWait";
								AddQuestRecord("SharkGoldFleet", "13");
								SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
								dialog.text = "Van egy kis dolgom... És neked jó hajód van. Csak most nem értem, hogy mit akarsz cserélni... Azt mondtad, hogy Porto Bellóba mész, hogy eladd az árut, de tudtommal nem tôlünk vetted a kolónián. Ne sértôdj meg, de nem úgy nézel ki, mint egy kereskedô. Nem vállalhatom ezt a kockázatot.";
								link.l1 = "Értettem... Hát, köszönöm szépen.";
								link.l1.go = "exit";
							}
							else
							{
								dialog.text = "Nekem dolgom van. Persze, nem ismerem magát... De az igazat megvallva, én csak olyan kereskedôkre emlékszem, akiknek a nevükön van a század. A többire nem. Igen, és van egy hosszú távú engedélyed, azonnal láthatsz egy tapasztalt kereskedôt. A hajója azonban érdekes. Miért kereskednél egy fregatton?";
								link.l1 = "Hah, ez nem egy átlagos fregatt. Még teli rakodótérrel is képes nagyon nagy sebességet elérni. Mindig könnyebb elmenekülni a kalózok elôl, mint harcolni ellenük, nem igaz? Bár a hajóm kisebb kapacitású, mint a közönséges kereskedelmi hajók, a kockázat sokkal kisebb.";
								link.l1.go = "SharkGoldFleet_01";
							}
						}
						
					}
					
				}
			}
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "Hmm, de igazad van! A spanyolok tudják, hogyan kell hajókat építeni, nem igaz? Igen, igen, azonnal láttam, hogy ez a jóképû férfi elhagyta a hajógyáraink készleteit. És igen, ma valóban azt mondták nekem, hogy egy adag kávét és kakaót vásárolt a kereskedônktôl, hogy Porto Bellóban továbbértékesítse. Jó üzlet, mondhatom. A kereskedelemben járatlan emberek nem tudják, hogy ezek az áruk itt olcsók, hála az ültetvényeknek, Porto Bellóban pedig nagy a kereslet rájuk, hiszen onnan a metropoliszba mennek.";
			link.l1 = "Nos, errôl szól az egész, senor. Néhány pezóért én nem vinném olyan messzire a hajómat.";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "Nos, az igazat megvallva, van egy kis dolgom magával. És nagyon jó, hogy ilyen gyors hajója van, ami vészhelyzetben vissza is tud vágni.";
			link.l1 = "Várjon, senor... Az ön ügye azt sugallja, hogy harcolnom kell...?";
			link.l1.go = "SharkGoldFleet_03";
		break;
		
		case "SharkGoldFleet_03":
			dialog.text = "Nem, nem, nem! Valójában a feladatom a lehetô legegyszerûbb. Egy levelet kell eljuttatnia a Porto Bello-i kikötôi hatósághoz. A levél le van pecsételve, és nem lehet kinyitni. Senkinek sem kell beszélnie róla, levelezés... személyes. Személyesen adja át. A határidô tíz nap. Aztán már nem lesz jelentôsége.";
			link.l1 = "Ilyen egyszerû? És mennyit kapok érte?";
			link.l1.go = "SharkGoldFleet_04";
		break;
		
		case "SharkGoldFleet_04":
			dialog.text = "Ötezer pezó. Vegye úgy, hogy nem kell futárt küldenie Porto Bello-ba.";
			link.l1 = "És mit kérdezett rólam és a hajómról?";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			dialog.text = "Nem érdekes. Csak arról van szó, hogy a levelezés elég fontos, és biztosnak kell lennem abban, hogy eljut a címzetthez. Tehát semmi különös. A bürokrácia... Egy átlagember számára ezek a dokumentumok nem érdekesek.";
			link.l1 = "Nos, egyetértek. Hozzuk ide a papírjait. Amint megérkezem Porto Bellóba, elviszem ôket a kollégájának. Tíz nap alatt elintézem, ne aggódjon.";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			dialog.text = "Egy pillanat. Sajnálom, teljesen elfelejtettem a nevét. Megmondaná, kérem? Le kell írnom az iratokba.";
			link.l1 = "A nevem Andreas Garcia.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "Köszönöm. Szóval... Nagyszerû. Ne feledje, hogy önnek kell átadnia ezt a dokumentumot, és közvetlenül a címzett kezébe. Tessék. A díjat a Porto Bello-i kikötôi hatóság vezetôje adja át önnek. Jó utat!";
			link.l1 = "Köszönöm! Most pedig bocsásson meg.";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			DialogExit();
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToPB10", 0, 0, 10, false);
			else NewGameTip("Felfedezô mód: az idôzítô ki van kapcsolva.");
			AddCharacterSkillDontClearExp(pchar, SKILL_LEADERSHIP, 1);
			AddCharacterSkillDontClearExp(pchar, SKILL_SNEAK, 1);
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_SharkGoldFleet_1");
			AddQuestRecord("SharkGoldFleet", "14");
			pchar.questTemp.SharkGoldFleet = "toPBPortOffice";
		break;
		
		case "SharkGoldFleet_09":
			RemoveItems(PChar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_2");
			dialog.text = "Remek! Sokat segítettél nekem. Voltak nehézségek?";
			link.l1 = "Nem, nem voltak nehézségek. Igaz, a kollégája szidta önt: azt mondta, hogy önök itt mindannyian tévelygôk, mert nem futárhajót küldenek, hanem átutazó kereskedôket, és még a fizetést is a címzettre akasztják. Megfenyegetett, hogy panaszt fog írni Havannába ...";
			link.l1.go = "SharkGoldFleet_10";
		break;
		
		case "SharkGoldFleet_10":
			dialog.text = "Micsoda?! Én vagyok a kuruzsló?! Mit gondolt ott magáról? Elôször is, tartsa meg az öt... nem, hatezer pezót! Ôszintén sírva fakadok!";
			link.l1 = "Köszönöm. Köszönöm. Jó látni, hogy a kolléga tévedett a véleményében.";
			link.l1.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_11":
			AddMoneyToCharacter(pchar, 6000);
			dialog.text = "Másodszor pedig úgy tûnik, ez a gazember elfelejtette, hogy két hónappal ezelôtt hogyan akasztotta rám egy kereskedôhajó összes fenntartási költségét, amely Caracasból Porto Bellóba, majd onnan Havannába ment! És megegyeztünk, hogy az út második részét ô fizeti! És soha nem adta vissza a tartozást, de megígérte, hogy a múlt hónapban mindent kifizet! És én még mindig fösvény vagyok ... Igen, én magam is panaszt fogok írni ellene Havannába!";
			link.l1 = "Hát persze, hogy a madridi udvar szenvedélyeivel rendelkezik ...";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			AddQuestRecord("SharkGoldFleet", "20");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date)
			pchar.questTemp.SharkGoldFleet = "LightVarToShark";
			SetFunctionLocationCondition("SharkGoldFleetToShark", "Curacao", false);
			dialog.text = "Nem, ha belegondolok... Micsoda szemtelenség! Jó, majd én elintézem újra... És most kérem, hogy bocsásson meg nekem: Sürgôs dolgom van. Öröm volt önnel üzletelni!";
			link.l1 = "És sok szerencsét!";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_13":
			RemoveItems(PChar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_2");
			dialog.text = "Remek! Sokat segített nekem. Bár én küldtem nekik egy futár poggyászt, és egy átmenô hajóval küldték vissza a választ. Igen... És azután még mindig panaszkodnak, hogy itt ülnek a nyomorultak.";
			link.l1 = "Hát, talán megspórolták a pénzt a futárra...";
			link.l1.go = "SharkGoldFleet_14";
		break;
		
		case "SharkGoldFleet_14":
			AddMoneyToCharacter(pchar, 5000);
			AddQuestRecord("SharkGoldFleet", "20");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date)
			pchar.questTemp.SharkGoldFleet = "DifficultVarToShark";
			SetFunctionLocationCondition("SharkGoldFleetToShark", "Curacao", false);
			dialog.text = "Nem 'lehet', , hanem határozottan, mondom neked! Rendben, nem számít. Tessék, itt a munkád. És most rengeteg munkám van, elnézést.";
			link.l1 = "Hát, talán megspórolták a pénzt a futárra...";
			link.l1.go = "exit";
		break;
		// <-- на пару с Акулой
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
