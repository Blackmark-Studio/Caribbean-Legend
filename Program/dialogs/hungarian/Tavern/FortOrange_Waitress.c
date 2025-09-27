// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Kérdések, " + GetAddress_Form(NPChar) + "?", "Miben segíthetek, " + GetAddress_Form(NPChar) + "?"), ""+ GetSexPhrase("Hm, mi a nagy ötlet, " + GetAddress_Form(NPChar) + "? ","Már megint a furcsa kérdések? Toots, menj, igyál egy kis rumot vagy valamit...") +"", "Az egész nap folyamán ez a harmadik alkalom, hogy valamilyen kérdésrôl beszélsz..."+ GetSexPhrase(" Ezek a figyelem jelei?","") +"",
                          "További kérdések, gondolom, " + GetAddress_Form(NPChar) + "?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam", "Jelenleg nincs mirôl beszélnem."), "Nem, nem szép...",
                      "Szó sem lehet róla, kedvesem...", "Nem, milyen kérdéseket?...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica_W")
            {
                link.l1 = "Figyelj, asszony, azt mondják, hogy közel álltál a régi cimborámhoz, Francois Gontierhez. Nagyon közel...";
                link.l1.go = "Jamaica_ratW_1";
            }
			
			if (pchar.questTemp.Slavetrader == "FindRatJamaica_WP")
            {
				if (CheckCharacterItem(pchar, "jewelry43"))
				{
					link.l1 = "Elhoztam a nyakláncodat drágakövekkel. Tessék. Isten óvjon meg a jövôben a magadfajta nôktôl.";
					link.l1.go = "Jamaica_ratW_5";
				}
				else
				{
					link.l1 = "Jelenleg semmi. A nyakláncodat keresem.";
					link.l1.go = "exit";
				}
            }
			
		break;
		
		case "Jamaica_ratW_1":
            dialog.text = "Igen, azok voltunk. És akkor mi van? Nem vagyok férjes asszony, és azzal töltöm az idômet, akivel akarom. Francois egy nagyon tiszteletreméltó tengerész, nem úgy, mint a helyi halászok és farmerek. Ô olyan... Ó! És olyan szép ajándékokat adott nekem!";
            link.l1 = "Jól van, elég volt! Tudom, milyen tulajdonságokkal rendelkezik a társam, nem kell felsorolnod nekem. Nem érdekel, mi történt köztetek. Akár meg is házasodhattok, nem érdekel. Azonnal meg kell találnom ôt, érted? Tudod, hogy hová indult?";
            link.l1.go = "Jamaica_ratW_2";
        break;
		
		case "Jamaica_ratW_2":
            dialog.text = "Hé, hé... Te vagy a barátja, és nem tudod, hogy hova ment. Ez vicces!";
            link.l1 = "Ez nem vicces, asszony. Megbeszéltük, hogy Jamaikán találkozunk, és aztán egy közös utazás várt ránk... ha érted, mit mondok. Egyedül nem fogom tudni megcsinálni, ô pedig Isten tudja, hová indult!";
            link.l1.go = "Jamaica_ratW_3";
        break;
		
		case "Jamaica_ratW_3":
            dialog.text = "Értem. Nos, ha egy ilyen jövedelmezô utazás a küszöbön áll az ön számára, tekintve, hogy ön és Francois barátok... Elmondom, hová indult, de csak egy kis jutalomért.";
            link.l1 = "Igen, tudom, mi a helyzet. Mennyit akarsz?";
            link.l1.go = "Jamaica_ratW_4";
        break;
		
		case "Jamaica_ratW_4":
            dialog.text = "Ó, milyen bosszúálló! Nincs szükségem pénzre. Nem, valami különlegeset akarok. Francois megígérte, hogy ad nekem egy szép nyakláncot drágakövekkel. Már dicsekedtem vele a barátaimnak, ô meg egyenesen elment... Hozd ide a medált, és megmondom, hová ment, he-he!";
            link.l1 = "Te pimasz ribanc! Ti holland szajhák olyan mohók vagytok, mint amilyenek vagytok! Rendben, megkapod a nyakláncot.";
            link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_5");
			pchar.questTemp.Slavetrader = "FindRatJamaica_WP";
        break;
		
		case "Jamaica_ratW_5":
            dialog.text = "Ah, ez gyönyörû! Most már a barátaim is zöldülni fognak az irigységtôl!";
            link.l1 = "Küldd el nekik a részvétemet. Most pedig kezdj el beszélni. Hová indult Francois?";
            link.l1.go = "Jamaica_ratW_6";
			RemoveItems(PChar, "jewelry43", 1);
        break;
		
		case "Jamaica_ratW_6":
            dialog.text = "Igen, természetesen, uram. Francois elhajózott Kuba felé, Havannába.";
            link.l1 = "Köszönöm a drága borravalót, szajha. Csak ennyit akartam.";
            link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_6");
			pchar.questTemp.Slavetrader = "FindRatHavana";
        break;
		
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
