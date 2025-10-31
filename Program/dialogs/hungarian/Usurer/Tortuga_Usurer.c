// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdései vannak?", "Miben segíthetek?"), "Nemrég próbálta ezt a kérdést feltenni nekem...", "Igen, hadd találjam ki... Már megint körbe-körbe jársz?",
                          "Figyelj, én itt a pénzügyekkel foglalkozom, nem válaszolok kérdésekre...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Jelenleg nincs mirôl beszélnem."), "Umph, hová tûnt a memóriám...",
                      "Kitaláltad, sajnálom...", "Megértem...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		case "tonzag_bail":
			dialog.text = "Helló, kapitány. Miben lehetek én és a cégem a szolgálatára?";
			link.l1 = "Szeretnék adományt tenni a Tortuga illusztris helyôrség nyugdíjalapjába.";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_1":
			dialog.text = "Megértem. Elég népszerû manapság! Mennyivel tartozik... Úgy értem, adakozni szeretne?";
			link.l1 = pchar.questTemp.TonzagQuest.Bail + " dublont. Mondja, elfogadja a pezót?";
			link.l1.go = "tonzag_bail_2";
		break;
		
		case "tonzag_bail_2":
			dialog.text = "Természetesen azonban ez egy kicsit drágább lesz az Ön számára. Hadd mondjam el pontosan... " + pchar.questTemp.TonzagQuest.Bail + " dublonok " + sti(pchar.questTemp.TonzagQuest.Bail) * 150 + " pezóba kerülnek.";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.TonzagQuest.Bail) || sti(pchar.money) >= sti(pchar.questTemp.TonzagQuest.Bail) * 150) {
				link.l1 = "Egy kicsit drágább, azt mondja? Tessék, a teljes szükséges összeg.";
				link.l1.go = "tonzag_bail_give";
			} else {
				link.l1 = "Egy kicsit drágább, azt mondod? Sajnos, jelenleg nincs nálam ennyi pénz. Lehetséges, hogy kölcsönt vegyek fel erre az ügyre?";
				link.l1.go = "tonzag_bail_loan";
			}
		break;
		
		case "tonzag_bail_give":
			dialog.text = "Csodálatos. Azonnal értesítjük a partnerét! Viszontlátásra, kapitány. És... sok szerencsét, már régóta várjuk a fellépését.";
			link.l1 = "Viszontlátásra.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			if (PCharDublonsTotal() >= sti(pchar.questTemp.TonzagQuest.Bail)) {
				RemoveDublonsFromPCharTotal(sti(pchar.questTemp.TonzagQuest.Bail));
			} else {
				AddMoneyToCharacter(pchar, -(sti(pchar.questTemp.TonzagQuest.Bail) * 150));
			}
			sld = CharacterFromID("TortugaJailOff");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "tonzag_bailed";
		break;
		
		case "tonzag_bail_loan":
			dialog.text = "Egy ilyen lehetôség mindig az ön számára elérhetô, kapitány! Mondjuk, kétszázezer pezó megtérüléssel hat hónapon belül?";
			link.l1 = "Nincs más választásom. Hol írjam alá?";
			link.l1.go = "tonzag_bail_give";
			
			pchar.quest.loans.tortuga.sum = 200000;
			pchar.quest.loans.tortuga.interest = 0;
			pchar.quest.loans.tortuga.period = 6;
			pchar.quest.loans.tortuga.StartDay = GetDataDay();
			pchar.quest.loans.tortuga.StartMonth = GetDataMonth();
			pchar.quest.loans.tortuga.StartYear = GetDataYear();
			pchar.quest.loans.tortuga.StartTime = GetTime();
			SetTimerCondition("Loans_Tortuga", 0, makeint(pchar.quest.loans.tortuga.period), 0, false);
			pchar.quest.Loans_Tortuga.CityId = "Tortuga";
			pchar.quest.Loans_Tortuga.win_condition = "LoansForAll";
			
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.TonzagQuest.Bail) * 150);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
