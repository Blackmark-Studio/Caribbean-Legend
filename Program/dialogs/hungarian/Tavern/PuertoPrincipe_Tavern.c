// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdései vannak?", "Miben segíthetek, " + GetAddress_Form(NPChar) + "?"), "Nemrég próbáltál feltenni nekem néhány kérdést, " + GetAddress_Form(NPChar) + "...", "Az egész nap folyamán ez a harmadik alkalom, hogy valamilyen kérdésrôl beszélsz...",
                          "További kérdések, gondolom?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Jelenleg nincs mirôl beszélnem."), "Umph, hová tûnt a memóriám...",
                      "Igen, ez tényleg a harmadik alkalom...", "Nem, milyen kérdéseket?...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Старые счёты
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_1"))
			{
				link.l1 = "Azt beszélik, hogy valaki megszabadította önt a drága ginjétôl. Vagy a pletykák hamisak?";
				link.l1.go = "OS_Tavern1_1";
			}
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_3"))
			{
				link.l1 = "Jó hír, "+npchar.name+"! Visszaszereztem a hordódat!";
				link.l1.go = "OS_Tavern3_1";
			}
		//<-- Старые счёты
		break;

		//--> Старые счёты
		case "OS_Tavern1_1":
			dialog.text = "Isten sebei, ez igaz. Mit hallottál még? Tudsz valamit? Könyörgöm, mondd, hogy tudod, hol találom. Ha nem találom meg... el kell menekülnöm ebbôl a városból. Vagy a saját lábamon, vagy egy fenyôládában.";
			link.l1 = "Valóban, a helyzeted komornak tûnik, barátom. Nem, én csak suttogást hallottam a szerencsétlenségedrôl. Hogy csúszhatott ki a kezeid közül egy ilyen értékes szállítmány?";
			link.l1.go = "OS_Tavern1_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Tavern1_2":
			dialog.text = "A pokolba az egésszel... Mit is mondhatnék? Az orrom elôl lopták el! A hordó reggel még biztosan itt volt. Két nappal ezelôtt érkezett, és a biztonság kedvéért egy éjszaka alatt hazavittem. Reggel visszahoztam, és a pult alá rejtettem. Estére pedig nyomtalanul eltûnt! Egy lélek sem látott vagy hallott semmit.";
			link.l1 = "Hát, átkozott legyek...";
			link.l1.go = "OS_Tavern1_3";
		break;

		case "OS_Tavern1_3":
			dialog.text = "Ha csak a leghalványabb sejtésem is lett volna, már rég levadásztam volna. De sajnos, semmi - mintha az a hordó túl finom lett volna ehhez a halandói birodalomhoz, és az égiek egyszerûen követelték volna. Százötven dublont fizetek annak, aki visszahozza. Sôt, még ennél is többet, egy táblát helyezek el a nevével a kocsmámban, hogy mindenki tudjon a hôstettérôl!";
			link.l1 = "Meglátom, mit tehetek. Majd késôbb visszatérünk erre az emléktábla ügyre. Mondd meg inkább, ki tudott errôl a hordóról? És ki állhatott rajtad kívül a pult mögött?";
			link.l1.go = "OS_Tavern1_4";
			link.l2 = "Százötven dublont egy hordóért? Mulatságos. De a te gondjaid nem az enyémek. Oldd meg magad.";
			link.l2.go = "OS_Tavern1_end";
		break;

		case "OS_Tavern1_end":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_1");
			CloseQuestHeader("OS");

			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.lifeday = 0;
				}
			}
			sld = CharacterFromID("OS_Pirate");
			sld.lifeday = 0;
		break;

		case "OS_Tavern1_4":
			dialog.text = "Gyakorlatilag senki! Kivéve talán a felszolgáló lányomat, de az lehetetlen. A taverna ritka jó hangulatban volt aznap - a 'Sea Beast' legénysége szép zsákmánnyal tért vissza a vadászatról. Egy perc pihenôje sem volt, nemhogy ideje a pultom mögé osonni.";
			link.l1 = "Biztos vagy benne?";
			link.l1.go = "OS_Tavern1_5";
		break;

		case "OS_Tavern1_5":
			dialog.text = "Kétségtelenül! A pihenés nélküli munka nem illett a vérmérsékletéhez, és estére már feszült volt, mint egy rugó. Amikor az egyik matróz közeledett hozzá, akkora lármát csapott, hogy majdnem megsüketült az egész üzlet. El kellett hagynom a helyemet, hogy helyreállítsam a rendet. Furcsa, bár - ô általában sokkal higgadtabban kezeli az ilyen közeledéseket.";
			link.l1 = "Ez minden? Semmi más szokatlan nem történt aznap?";
			link.l1.go = "OS_Tavern1_6";
		break;

		case "OS_Tavern1_6":
			dialog.text = "Amíg az elsô zavart elfojtottam, egy másik lángolt fel - két matróz összeverekedett a túlsó sarokban. A dulakodás azonban nem tartott sokáig; úgy tûnt, hogy hajótársak, és gyorsan szétváltak. Ezután minden lecsendesedett, és semmi említésre méltó nem történt.";
			link.l1 = "Rendben van, akkor megkezdem a keresést. Várj, azt hiszem, hamarosan a hordó újra a te, khm... figyelô szemed alá kerül.";
			link.l1.go = "OS_Tavern1_7";
		break;
		//<-- Старые счёты
		
		case "OS_Tavern1_7":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_1");
			AddQuestRecord("OS", "2");
			
			sld = GetCharacter(NPC_GenerateCharacter("OS_Matros_1", "citiz_31", "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
			sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
			sld.dialog.currentnode = "OS_Matros";
			LAi_SetImmortal(sld, true);
			sld.City = "PuertoPrincipe";
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_town", "goto", "goto14");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "OS_Tavern3_1":
			dialog.text = "Megtaláltad? Tényleg az lehet? Kapitány, megmentette az életemet! Ki állt emögött? Tudnom kell a gazember nevét!";
			link.l1 = "Ez egy aprólékosan megtervezett terv volt, amelyet egy bizonyos Jack Veils, aSea Beast kapitányával együttmûködve, a 'Sea Beast'. tengerészeket toboroztak, és egy bonyolult elterelést rendeztek, hogy elcsalják magukat. Amikor elhagytad a posztodat, a hordó ôrizetlenül maradt, és ôk könnyedén megléptek vele.";
			link.l1.go = "OS_Tavern3_2";
			DelLandQuestMark(npchar);
			pchar.questTemp.CameraDialogMode = true;
		break;

		case "OS_Tavern3_2":
			dialog.text = "Te jó ég! Jack Veils! Szóval visszatért... És úgy tûnik, hogy ilyen alattomos eszközökkel akarta visszaszerezni a kocsmát. Az a róka sosem ismeri be a vereséget!";
			link.l1 = "Szóval ô volt egykor ennek a létesítménynek a tulajdonosa? Biztos lehetsz benne, hogy nem fog újra ármánykodni. Elküldtem, hogy találkozzon a teremtôjével.";
			link.l1.go = "OS_Tavern3_3";
		break;

		case "OS_Tavern3_3":
			dialog.text = "Kapitány! Ez rendkívüli! Megszabadítottál... megszabadítottál az állandó rettegéstôl, ami beárnyékolta a napjaimat! Mindig is tudtam, hogy elôbb-utóbb visszatér... Néhány évvel ezelôtt riválisok voltunk ennek a kocsmának a tulajdonjogáért, és neki sikerült legyôznie engem\nA gyôzelem öröme azonban a vesztét okozta - ünnepi mértéktelenségében akaratlanul is elkártyázta nekem a helyet. Persze, reggelre elrohant, és könyörgött, hogy visszaszerezze a kocsmát, bármit és mindent ígérve\nDe én nem vagyok teljesen bolond, hogy ilyen feltételekbe beleegyezzek. Aztán eltûnt... Tudtam, hogy nem hagyja annyiban a dolgot. Éreztem, hogy egy nap visszatér. És most eljött ez a nap.";
			link.l1 = "Elismerésem, hogy ravaszul hajtotta végre a tervét.";
			link.l1.go = "OS_Tavern3_4";
		break;

		case "OS_Tavern3_4":
			dialog.text = "Várj egy pillanatot! Honnan tudott egyáltalán a hordóról? Úgy tûnik... úgy tûnik, kezdem megérteni! A pincérnô! Ezért menekült el, mint egy leforrázott macska, búcsú nélkül. Biztos megneszelte, hogy elintézted Jacket. Most már minden a helyére került. Kapitány, mérhetetlenül hálás vagyok magának, maga...";
			link.l1 = "...";
			link.l1.go = "OS_Tavern3_5";
		break;
		
		case "OS_Tavern3_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_3");
			ChangeShowIntarface();
			
			sld = GetCharacter(NPC_GenerateCharacter("OS_Zaharia", "Marlow", "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
			sld.name = GetCharacterName("Zachary");
			sld.lastname = GetCharacterName("Marlow");
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_tavern", "reload", "reload1");
			TeleportCharacterToPosAy(sld, -1.30, 0.00, -0.67, 1.50);
			sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
			sld.dialog.currentnode = "Zaharia_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		
		//<-- Старые счёты
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
