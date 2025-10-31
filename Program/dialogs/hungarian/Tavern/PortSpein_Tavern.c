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
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption") && pchar.questTemp.Consumption == "begin" && sti(pchar.money) >= 3000)
			{
				link.l1 = "Úgy hallottam, hogy a fogyasztás elszabadult az erôdben. Gondolod, hogy a járvány átterjed a városra?";
				link.l1.go = "Consumption";
			}
			if (CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.Commandant") && pchar.questTemp.Consumption == "begin")
			{
				link.l1 = "Mit tudsz mondani az erôd parancsnokáról?";
				link.l1.go = "Consumption_8";
			}
			if (!CheckAttribute(npchar, "quest.Consumption_1") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Mondd csak, jelent neked valamit a név 'Juan' ?";
				link.l1.go = "Consumption_12";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Figyeljen, 1654 áprilisában egy fregatt kötött ki a kikötôjükben Miguel Dichoso kapitány parancsnoksága alatt, aki utána eltûnt. Tud valamit mondani errôl?";
				link.l1.go = "guardoftruth";
			}
			//--> Оковы Азарта
			if (CheckAttribute(pchar, "questTemp.OZ_Tavern_1"))
			{
				link.l2 = "Mondd meg nekem, "+npchar.name+", miféle ember ez a Javier Castillo?";
				link.l2.go = "OZ_Tavern_1";
			}
			if (CheckAttribute(pchar, "questTemp.OZ_Tavern_2"))
			{
				link.l2 = "Térjünk vissza ahhoz a beszélgetéshez arról az emberről, aki hatással lehet Javierre.";
				link.l2.go = "OZ_Tavern_2_1";
			}
			//<-- Оковы Азарта
		break;
		
		//--> Цена чахотки
		case "Consumption":
			dialog.text = "A parancsnok azt állítja, hogy nincs veszélyben. Aki túl kíváncsi, azt a kazamatákba zárják. Én nem tartozom közéjük, sajnálom.";
			link.l1 = "Valóban? Egy kocsmárosnak nincs kedve pletykákat hallgatni - ez újdonság! Lehet, hogy a pezsgô csilingelése visszaadja a kíváncsiságodat?";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "Az ezüst persze csábító, de a saját bôröm értékesebb. Talán valami másról is mesélhetnék, senor? Igazából mindig szívesen beszélgetek, csak kezdje el a beszélgetést!";
			link.l1 = "Szóval így alakul a dolog... Rendben, ebben az erszényben van nyolcezer, és egy jót beszélgetünk az idôjárásról, megegyeztünk?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			AddMoneyToCharacter(pchar, -3000);
			dialog.text = "Ó, maga aztán kitartó, senor. Csak ne feledje, hogy ez a beszélgetés sosem történt meg. (suttogás) Már egy egész éve többször hallottam, hogy emberek égnek a börtöneinkben, haldokolnak a fogyasztás miatt. Lehet hibáztatni a hatóságokat, lehet hibáztatni Istent, vagy az ördögöt, de a legtöbbet a balszerencsének tulajdonítják. Ez az átkozott betegség olyan gyorsan lopja el az életeket.  Néha betesznek egy teljesen egészséges embert, és egy-két héten belül meghal. Csak úgy...";
			link.l1 = "Hûha... Egy egész év, azt mondja? És mi van, senki sem tett semmit ellene?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "Kit érdekel, senor? Kit érdekelnek a foglyok? A társadalom söpredéke - mondják a selyem nagyjai. Volt egy orvos, aki a tömlöcben dolgozott. Megpróbálta meggyógyítani azokat a szegény lelkeket. Nem sokáig bírta, úgy látszik, a betegség ôt is megszabadította\nA parancsnok most már nem engedi be az embereket, és a mi hatóságaink nem figyelnek az ilyen dolgokra, fôleg, ha kevesebbet kell fizetniük a börtönadagért.";
			link.l1 = "Érdekes, de mi az a betegség, ami annyira megrémít, hogy biztonságos falak közé zárva úgy suttogunk, mint apácák a gyóntatószékben?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Nehéz megmondanom, de volt itt egy fickó. Csempészetért vitték be, és körülbelül fél évig volt bezárva, amíg a haverjai ki nem vásárolták. Hát, tudod -mérték le az aranyat annak, akinek kellett, annyit vártak, amennyit mondtak, és a fickó kiszabadult. De azóta eléggé meg van ôrülve.";
			link.l1 = "Ôrültebb, mint egy patkány?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "Gondolom. Azóta használhatatlan volt a társai számára, az egész napot itt töltötte, és halálra itta magát. Úgy nézett ki, mintha ki akart volna törölni valamit a fejébôl. Minden alkalommal, amikor berúgott, történeteket mesélt a fogyasztásról, ami csendben elviszi az embereket\nEzek voltak a pontos szavai. Szerinte a 'fogyasztás' a legrosszabb dolog, ami egy emberrel történhet.";
			link.l1 = "Egy részeg ember zagyvaságai. Mi van vele?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			if (CheckAttribute(pchar, "questTemp.Consumption.Commandant"))
			{
				dialog.text = "Semmi, azon kívül, hogy talált egy kis folyékony bátorságot, és egyre többet és többet kezdett beszélni, aztán valaki csak úgy elvágta a torkát, és a csatornába dobta... és hogy ki tette, és miért, az nekem mindegy.";
				link.l1 = "Mit lehet mondani a parancsnokról?";
				link.l1.go = "Consumption_8";
			}
			else
			{
				dialog.text = "Semmi, csak az, hogy bátor lett, és egyre többet és többet kezdett beszélni, aztán egyszer csak valaki elvágja a torkát, és bedobja a csatornába... és hogy ki tette, és miért, az nekem mindegy. (emeli fel a hangját) Igen, az öblök és a zátonyok nagyon veszélyesek itt, senor. Óvatosnak kell lenni, amikor a Nagy-Antillák felôl viharok zúdulnak ránk, elszalasztja az idôjárásjelzôt, és már el is tûnt! Jó pihenést, senor, köszönöm, hogy benézett!";
				link.l1 = "Viharok... igen. Neked is köszönöm.";
				link.l1.go = "Consumption_7";
			}
			pchar.questTemp.Consumption.Contra = "true";
		break;
		
		case "Consumption_7":
			DialogExit();
			npchar.quest.Consumption = "true";
			AddQuestRecord("Consumption", "2");
		break;
		
		case "Consumption_8":
			dialog.text = "Mit is mondhatnék róla? Ezredes, pár éve érkezett Európából, miután megkapta ezt a helyet. Állítólag lefokozták ott az Óvilágban valami piszkos ügyei miatt, amibe belekeveredett. Nem tudom, hogy igaz-e, de eleinte voltak pletykák. De hát kinek nincsenek pletykái, nem igaz?";
			link.l1 = "Mocskos tettek, azt mondod... Ez érdekes. Van még valami?";
			link.l1.go = "Consumption_9";
		break;
		
		case "Consumption_9":
			dialog.text = "Nos, mit is mondhatnék... Az ezredes olyan embernek látszik, aki mélyen aggódik a saját biztonságáért. Persze, ezek a helyek nem biztonságosak a kalózok, banditák, indiánok és egyéb söpredék miatt, de Senor Commandant soha nem hagyja el a házát több testôr nélkül\nEz a városban van a kúriája, amit egy kis erôddé alakított - a szolgái jól felfegyverkezve tartják az ablakokat rács mögött.";
			link.l1 = "De napközben a börtönben teljesít szolgálatot, nem igaz?";
			link.l1.go = "Consumption_10";
		break;
		
		case "Consumption_10":
			dialog.text = "Igen, de az a kúria alapvetôen ott vár egy rajtaütésre vagy invázióra. Különben is, Senor Commandant nem gyakran tér vissza oda ténylegesen nyilvánvalóan egy igazi erôd inkább az ô erôdje, he-he.";
			link.l1 = "Köszönöm, nagy segítség volt. Viszlát késôbb, "+npchar.name+"!";
			link.l1.go = "Consumption_11";
		break;
		
		case "Consumption_11":
			DialogExit();
			if (CheckAttribute(npchar, "quest.Consumption")) AddQuestRecord("Consumption", "4");
			else AddQuestRecord("Consumption", "5");
			DeleteAttribute(pchar, "questTemp.Consumption.Commandant");
			pchar.questTemp.Consumption = "current";
		break;
		
		case "Consumption_12":
			dialog.text = "Juan? Melyik? Sokan vannak itt, az embereknek általában van vezetéknevük is... vagy legalábbis becenevük...";
			link.l1 = "Csak arra gondoltam... Lehet, hogy a beceneve 'Fogyasztás', hallottál már ilyet?";
			link.l1.go = "Consumption_13";
		break;
		
		case "Consumption_13":
			dialog.text = "Istenem, már megint errôl beszélsz! Nem, hála Istennek, nem hallottam. Esküszöm! És most váltsunk témát. Kérem!";
			link.l1 = "Jól van, rendben, ne kapj szívrohamot...";
			link.l1.go = "exit";
			pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan)+1;
			if(sti(pchar.questTemp.Consumption.AskJuan) == 3)
			{
				pchar.quest.Consumption2.win_condition.l1 = "location";
				pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
				pchar.quest.Consumption2.function = "Consumption_CreateSergio";
			}
			npchar.quest.Consumption_1 = "true";
		break;
		//<-- Цена чахотки
		
		//--> Оковы Азарта
		case "OZ_Tavern_1":
			dialog.text = "Javier egy kártyás, csaló és szélhámos. Folyton a fogadóban lóg, és keresi, kitől szerezhetne pár pesót.";
			link.l1 = "Tehát más sötét ügyekben nem volt észrevéve? Talán vannak ellenségei?";
			link.l1.go = "OZ_Tavern_2";
			DeleteAttribute(pchar, "questTemp.OZ_Tavern_1");
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Tavern_2":
			dialog.text = "Nos, mondjuk úgy, hogy barátja jóval kevesebb van, mint azoknak, akik arról álmodoznak, hogy kitekerjék a nyakát. De ha szüksége van egy névre, aki valóban hatással lehet rá, az ezer pesóba fog kerülni. Fizet, és mindent elmondok.";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Rendben, tessék a pénzed, te vén zsaroló.";
				link.l1.go = "OZ_Tavern_3";
			}
			else
			{
				link.l1 = "Térjünk vissza ehhez a beszélgetéshez később. Most nincs nálam ennyi.";
				link.l1.go = "exit";
				pchar.questTemp.OZ_Tavern_2 = true;
				AddLandQuestMark(npchar, "questmarkmain");
			}
		break;
		
		case "OZ_Tavern_2_1":
			dialog.text = "Kapitány, meghozta az ezer pesót?";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Meghoztam. Tessék, te vén zsaroló.";
				link.l1.go = "OZ_Tavern_3";
			}
			else
			{
				link.l1 = "Ördögbe. Hamarosan visszatérek.";
				link.l1.go = "exit";
			}
		break;
		
		case "OZ_Tavern_3":
			dialog.text = "Na, ez már más beszéd. Tudja, Javiernek nem csak kártyaadósságai vannak. Egyszer úgy döntött, hogy antikvitás-kereskedelembe kezd, de ahogy várható volt, ez nem a legjobban sült el számára. Eleinte még egész jól ment az üzlet, de aztán adódott egy lehetőség, hogy megszerezzen egy ritka darabot\nAnnyira belelkesedett, hogy minden uzsoráshoz elment pénzért. Természetesen senki nem adott neki egy fillért sem. Akkor talált egy hozzá hasonlóan antikvitásokért rajongó embert, és kölcsönkért tőle százötvenezer pesót. Gondolom, sejti a folytatást\nRútul rászedték, és most ez az adósság úgy lóg rajta, mint egy kő a nyakán. Csak filléreket fizetett vissza, és úgy tűnik, a többit nem is áll szándékában megadni, annak ellenére, hogy a hitelezője már embereket is fogadott, hogy megfélemlítsék\nAz az ember, akinek tartozik – Felipe Alarcón. A háza a bankkal szemben van, könnyen felismeri: pompás kúria, oszlopokkal a bejáratnál.";
			link.l1 = "Köszönöm!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000);
			DeleteAttribute(pchar, "questTemp.OZ_Tavern_2");
			AddDialogExitQuestFunction("OZ_Felip_1");
			DelLandQuestMark(npchar);
		break;
		//<-- Оковы Азарта
		
		case "guardoftruth":
			dialog.text = "Emlékszem rá. Gyakran megfordult a kocsmámban, de nem sokat beszélgettünk. Megivott néhány feles rumot, suttogott néhány vendéggel, és elment. Nagyon komor és komoly, mint mindenki azon a fregatton. Veszélyes kinézetû zsoldosok, akik készenlétben tartották a pengéjüket\nVolt egy pletyka, hogy a fregatt tele volt kincsekkel, de én nem hiszek az ilyen mesékben. Értékes rakományt soha nem szállítanak egyetlen hajóval konvoj nélkül. Egy napot töltöttek itt, aztán elmentek. Úgy hallottam, Európába. Csak ennyit tudok.";
			link.l1 = "Értem. Nos, ez legalább valami...";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
			AddQuestRecord("Guardoftruth", "40");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
