// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdései vannak?", "Miben segíthetek?"), "Nemrég megpróbált feltenni nekem egy kérdést...", "Ilyen kíváncsi emberekkel még nem találkoztam sem a hajógyáramban, sem máshol ebben a városban.",
                          "Mi ez a sok kérdés? Az én munkám az, hogy hajókat építsek. Gondoskodjunk errôl.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Jelenleg nincs mirôl beszélnem."), "Umph, hová tûnt a memóriám...",
                      "Hm, nos...", "Folytasd csak...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx"))
            {
				if (pchar.questTemp.Mtraxx == "silk_2" || pchar.questTemp.Mtraxx == "silk_3")
				{
					link.l1 = "Úgy hallottam, ez a hajógyár a hajó sebességének javításával foglalkozik. Ehhez selyem vitorlavászonra van szükség, ami nagyon ritka. Szeretne... beszélni errôl?";
					link.l1.go = "mtraxx";
				}
			}
			if (CheckAttribute(npchar, "quest.upgradeship")) {
				link.l2 = "Miss MacArthurtól jöttem, ami a...";
				link.l2.go = "helen_upgradeship";
			}
			
			if (CheckAttribute(npchar, "quest.upgradeship.money") && HelenCanUpgrade()) {
				link.l2 = "Kezdjék meg a hajó felújítását!";
				link.l2.go = "helen_upgradeship_money";
			}
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
            dialog.text = "Lehetne ennél világosabb, fiatalember? Pontosan mi hozta ide? Ha javítani akar a hajóján - térjünk rá azonnal az üzletre.";
			link.l1 = "Nem teljesen. Az Ön által végzett szolgáltatások típusához olyan árukra van szükség, amelyek nem állnak szabadon rendelkezésre a boltban. Szeretném felajánlani önnek azokat az anyagokat, amelyekre szüksége lehet.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Nos, nos... Hmm... Tudja, hogy csak a gyarmat hatóságai jogosultak ilyen stratégiai fontosságú árukkal kereskedni? Szabadon biztosíthatja a saját selymét, hogy a hajója javításán dolgozhassak, azonban az eladása szigorúan tilos. Ahogy a tôlem való megvásárlása is - az ilyen tevékenységet meglehetôsen szigorúan megbüntetik.";
			link.l1 = "Nos, ez nem egy bolt, és nem is vámhivatal...";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Az összes selyemvitorlavásznat közvetlenül az ügyfeleimtôl szerzem be, vagy a kormányzó külön engedélyével korlátozott mennyiséget vásárolok. Ha nincs több kérdése, akkor kérem, hadd térjek vissza a munkámhoz.";
			link.l1 = "Hmm... Rendben. Szép napot, mester.";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            DialogExit();
			AddQuestRecord("Roger_2", "5");
			pchar.questTemp.Mtraxx = "silk_4";
		break;
		
		case "helen_upgradeship":
			dialog.text = "Ó, tudom! Szerencsés vagy, kapitány. A hajó teljes felújításáról van szó? Mindent elintézünk; a mi hajógyárunk a plymouthiakkal vetekszik!";
			link.l1 = "Gondolom, ez nem lesz ingyenes szolgáltatás?";
			link.l1.go = "helen_upgradeship_1";
		break;
		
		case "helen_upgradeship_1":
			dialog.text = "Természetesen, kapitány, az ilyen szolgáltatások nem lehetnek ingyenesek, még Cromwell számára sem! Azonban tartom a szavam, és csak pénzt fogadok el - nem kell csempészni.";
			link.l1 = "Érthetô. Mennyiért?";
			link.l1.go = "helen_upgradeship_2";
		break;
		
		case "helen_upgradeship_2":
			dialog.text = "A zászlóshajó méretétôl függ, kapitány. Egy elsô rangú hajó ötezer dublonnába kerül, egy ötödik rangú pedig csak ezer dublonnába.";
			link.l1 = "Rendben, majd jövök, ha döntöttem.";
			link.l1.go = "exit";
			
			npchar.quest.upgradeship.money = true;
		break;
		
		case "helen_upgradeship_money":
			dialog.text = "Kiváló, most már mindenem megvan, amire szükségem van. Akkor elkezdek dolgozni.";
			link.l1 = "Várok.";
			link.l1.go = "helen_upgradeship_money_1";
			
			iTemp = GetCharacterShipType(pchar);
			sld = GetRealShip(iTemp);
			iTemp = (7 - sti(sld.class)) * 1000;
			RemoveDublonsFromPCharTotal(iTemp);
		break;
		
		case "helen_upgradeship_money_1":
			AddTimeToCurrent(6, 30);
			dialog.text = "... Azt hiszem, ennyi volt... A minôség garantált.";
			link.l1 = "Köszönöm! Majd megnézem.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenUpgradeShip2");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

bool HelenCanUpgrade() {
	int shipIndex = GetCharacterShipType(pchar);
	if (shipIndex == SHIP_NOTUSED) {
		return false;
	}
	
	sld = GetRealShip(shipIndex);
	if (sti(sld.class) == 7) {
		return false;
	}
	
	int cost = (7 - sti(sld.class)) * 1000;
	return (PCharDublonsTotal() >= cost);
}
