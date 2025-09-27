// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Mit akarsz? Kérdezzen csak.", "Figyelek rád, mi a kérdés?"), "Már másodszor próbálod megkérdezni...", "Már harmadszorra próbálod újra megkérdezni...",
                          "Mikor lesz már vége?! Elfoglalt ember vagyok, a kolónia ügyein dolgozom, és te még mindig próbálsz kérdezni valamit!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Most nem. Rossz helyen és rossz idôben."), "Igaz... De késôbb, nem most...",
                      "Megkérdezem... De egy kicsit késôbb...", "Sajnálom, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);			  
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Volt egy jövedelmezô üzletem Martinique-on, és most azt tervezem, hogy Blueweldre hajózom. Vörösfenyôt és kávét akarok venni a kolónián. Emellett a briggem nem bírja el azt a sok rakományt, amit hajlandó vagyok megvenni, ezért itt a hajógyáratokban kell vennem egy furulyát. Segítene nekem ezekben az ügyekben?";
                link.l1.go = "MayorDone";
            }
		break;
		
		case "MayorDone":
			dialog.text = "Az én segítségem? A kereskedônk nagyon becsületes ember, így kétlem, hogy megpróbálná átverni önt. Beszélj a hajóskapitánnyal a fuvoláról, ô majd segít neked ebben az ügyben. És ha mégis bajba kerülsz, akkor gyere el hozzám. Érdekel a kereskedelmi kapcsolatok fejlesztése a gyarmatunkkal, és minden támogatásomat kifejezem neked.\nAmellett ma este bankettet szervezek, Bridgetown összes legragyogóbbja részt vesz rajta. Önnek is el kellene jönnie, kapitány.";
			link.l1 = "Köszönöm a meghívást, de sajnos túl elfoglalt vagyok. Viszontlátásra és köszönöm az ügynöki tevékenységét!";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-8");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
			AddQuestRecord("Holl_Gambit", "2-6");
			pchar.questTemp.HWIC.Eng = "SeekVanBerg";
			pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
			DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
				//if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_VALCIRIA || GetCompanionQuantity(pchar) > 1) AddDialogExitQuestFunction("FailVanBergInWorld");
				//else AddDialogExitQuestFunction("CreateVanBergInWorld");
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
