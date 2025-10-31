void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
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
			dialog.text = "Mit szeretne?";
			link.l1 = "Semmi.";
			link.l1.go = "exit";
		break;

		case "Poorman_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "Hé, szépségem, mit szólnál egy gyönyörû díszhez a hölgyed gyûjteményébe? Egy igazi kincs! Neked - csodáló pillantások, nekem - néhány pénzérme kenyérre és egy korty rum.";
			}
			else
			{
				dialog.text = "Hé, Cap, mit szólnál egy remek ajándékhoz a hölgyednek? Egy igazi kincs! Neked - a szívélyes hálája, nekem - néhány pénzérme kenyérre és egy korty rum.";
			}
			link.l1 = "Hogy egy óra múlva katonák jöjjenek értem, és börtönbe zárjanak lopásért? Honnan szerezted, csavargó?";
			link.l1.go = "Poorman_2_fortune";
			link.l2 = "Egy gyönyörû ajándékot? És honnan szerezhet ilyesmit egy magadfajta hajléktalan?";
			link.l2.go = "Poorman_2_leadership";
			if (npchar.quest.meeting == "0") npchar.quest.meeting = "1";
		break;

		case "Poorman_2_fortune":
			dialog.text = ""+GetSexPhrase("Cap, I","I")+" találtam ezt a gyönyörû medált egy kámeával, ôszinte szóval! Elsüllyedhetek ha hazudok! Csak úgy ott hevert, nem kívántan. Nem hagyhattam volna ilyen szépséget a mocsokban, ugye?";
			link.l1 = "Hát persze. Mutasd meg, mi van ott!";
			link.l1.go = "Poorman_3";
			link.l2 = "Ki hinné el egy ilyen tiszteletreméltó úriember szavát, mint maga? Találjon valaki mást, aki hiszékenyebb.";
			link.l2.go = "Poorman_exit";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "Poorman_2_leadership":
			dialog.text = ""+GetSexPhrase("Cap, I","I")+" találtam ezt a gyönyörû medált egy kámeával, ôszinte szóval! Elsüllyedhetek ha hazudok! Csak úgy ott hevert, nem kívántan. Nem hagyhattam volna ilyen szépséget a mocsokban, ugye?";
			link.l1 = "Hát persze. Mutasd meg, mi van ott!";
			link.l1.go = "Poorman_3";
			link.l2 = "Ki hinné el egy ilyen tiszteletreméltó úriember szavát, mint maga? Találjon valaki mást, aki hiszékenyebb.";
			link.l2.go = "Poorman_exit";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Poorman_exit":
			DialogExit();
			AddDialogExitQuestFunction("TBP_PismoVDome");
		break;
		
		case "Poorman_3":
			dialog.text = "Nézze... ez egy nagyon szép dolog! Egy virágágyásban találtam, a lámpás ház mellett, a kocsma mellett. De már régóta nincs ott senki, így nincs kinek visszaadni.";
			link.l1 = "Különös kis csecsebecse. És mennyit kér érte?";
			link.l1.go = "Poorman_4";
		break;

		case "Poorman_4":
			dialog.text = "Csak száz peso"+GetSexPhrase(", Cap","")+"... csupán fillérek egy olyan valakinek, mint te! Nekem pedig - egy egész hétig nem kell aggódnom, hogy hol kapok egy darab kenyeret. Csak nézd meg - micsoda szépség!";
			if (sti(pchar.Money) >= 100)
			{
				link.l1 = "Rendben, itt van a száz pezód.";
				link.l1.go = "Poorman_5";
			}
			link.l2 = "Azt hiszem, kihagyom. Próbáljon szerencsét valaki mással.";
			link.l2.go = "Poorman_exit";
		break;

		case "Poorman_5":
			dialog.text = "Köszönöm, "+GetAddress_Form(NPChar)+"! Most már biztos, hogy a szerencse rád mosolyog! Te jó ember vagy, ez könnyen látható.";
			link.l1 = "...";
			link.l1.go = "Poorman_exit";
			GiveItem2Character(PChar, "jewelry24");
			pchar.questTemp.TBP_BuyKulon = true;
			pchar.questTemp.TBP_BuyKulonOtdatBetsy = true;
		break;
		
		case "Pirate_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "O-o-o-oh, ki jött meglátogatni minket? Úgy tûnik, nem rossz ajtón jöttél, édesem... gyere be, gyere be! Vedd le a ruháidat, érezd magad otthon.";
				link.l1 = "Nocsak, nocsak... Ki van itt? Nem ugyanazok a gazemberek, akik azt a 'tender' fenyegetô üzenetet hagyták Betsynek?";
			}
			else
			{
				dialog.text = "És m-m-milyen tintahal ez?! Rossz ajtón jöttél be, te kecskefejû? Tûnj innen, mielôtt kibelezlek!";
				link.l1 = "Nocsak, nocsak... Ki van itt? Nem ti vagytok azok a bolondok, akik azt a szép fenyegetô üzenetet hagyták Betsy-nek?";
			}
			link.l1.go = "Pirate_2";
		break;

		case "Pirate_2":
			if (pchar.sex == "woman")
			{
				dialog.text = "Betsy? A pokolba azzal a Betsy-vel! Sokkal érdekesebb, hogy mit keresel itt, édesem... Ha már itt vagy - nem kell elrohanni, majd kitalálunk valamit, amivel lefoglaljuk...";
			}
			else
			{
				dialog.text = "Mi az ördögöt csinálsz, Betsy? Ne kísértsd a sorsot, te bolond. Amíg a saját lábadon el tudsz menni - menj el. Különben darabonként kell összeszednünk és vödörben kivinnünk!";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_2");
		break;

		case "BetsiPrice_1":
			dialog.text = "Segítség! Segítség, könyörgöm!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_3");
			locCameraFromToPos(1.40, 1.62, 1.14, false, 2.58, -0.30, -1.64);
		break;
		
		case "Pirate_3":
			dialog.text = "...";
			link.l1 = "És ott van. Fülig érô bajban vagy, barátom, és ha nem akarod, hogy ez legyen az utolsó hibád, azt tanácsolom, hogy engedd el. Azonnal.";
			link.l1.go = "Pirate_4";
		break;

		case "Pirate_4":
			dialog.text = "Ha! Hallottad ezt, Reggie? "+GetSexPhrase("Ô","Ô")+" még minket is fenyeget. "+GetSexPhrase("Micsoda pimasz csiga","Micsoda pimasz szemét")+". Hé, mutassuk meg "+GetSexPhrase("ennek a fellengzôsnek, hogy milyen színûek a belei","ennek a fellengzôsnek, hogy milyen az igazi fájdalom")+".";
			link.l1 = "Ez a te temetésed.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_4");
		break;

		case "Pirate_5":
			if (!CharacterIsAlive("TBP_Bandit_1"))
			{
				dialog.text = "...";
				link.l1 = "Most engedd el a lányt. Vagy a barátod mellett fogsz feküdni.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("TBP_HouseBetsi_6");
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Pirate_5";
			}
		break;

		case "BetsiPrice_2":
			dialog.text = "Átkozott kutyák! Azt hittétek, hogy csendben maradok?!";
			link.l1 = "...";
			link.l1.go = "BetsiPrice_2_1";
			sld = CharacterFromID("TBP_Bandit_2");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("TBP_BetsiPrice"));
			CharacterTurnByChr(npchar, sld);
		break;

		case "BetsiPrice_2_1":
			dialog.text = "És te... Nem úgy tûnik, mintha velük lennél. Ki vagy te?";
			link.l1 = "Kapitány "+GetFullName(pchar)+", szolgálatára.";
			link.l1.go = "BetsiPrice_2_2";
			CharacterTurnByChr(npchar, pchar);
		break;

		case "BetsiPrice_2_2":
			dialog.text = "Szóval, az életemmel tartozom neked?";
			link.l1 = "Úgy néz ki. De most valami más fontosabb - kik ezek az emberek és mibe keveredtél?";
			link.l1.go = "BetsiPrice_3";
		break;
		
		case "BetsiPrice_3":
			dialog.text = "Ezek az emberek... Egy fontos angol tisztviselô küldte ôket. Egykor nagyon közel állt hozzám... és most, mint látod, a halálomat kívánja.";
			link.l1 = "Azt hiszem, kezdem érteni a történetét. A szeretôje voltál, de egy bizonyos ponton úgy döntöttél, hogy ezt kihasználhatod. Meg akarta ijeszteni... elmondta a családjának?";
			link.l1.go = "BetsiPrice_4";
		break;

		case "BetsiPrice_4":
			dialog.text = "Meglepôen közel vagy"+GetSexPhrase(" az igazsághoz, jóképû"," az igazsághoz, cukorfalat")+"... és ugyanakkor nagyon messze is tôle. Ha ez lenne a helyzet, már rég halott lennék. Igen, a szeretôje voltam, de eszembe sem jutott családi drámákat kreálni\nAz egész sokkal bonyolultabb volt: egy nap megtudtam, hogy új játékszerre talált magának, és úgy döntött, megszabadul tôlem, üres kézzel hagyva engem. Csak úgy kidobott, mint egy nem kívánt dolgot. Nos, én nem szoktam a semmivel távozni\nSzóval fogtam, ami igazán értékes volt - papírokat, amelyek tönkretehették volna az életét -, és elmenekültem az Újvilágba. Aztán alkut ajánlottam: a titkait a biztonságomért és bôkezû kártérítésért cserébe\nEzért vagyok még életben - szükségük van az iratokra. És nem siettem el, hogy felfedjem, hol vannak elrejtve.";
			link.l1 = "Nos, te nemcsak gyönyörû vagy, hanem ördögien ravasz is. Bátran játszottál, de legyünk ôszinték - ez a játék már kicsúszott az irányításod alól. Talán itt az ideje, hogy elgondolkodj egy másik lehetôségen, amíg még van esélyed arra, hogy megpróbálj kilépni a játékból? Ha itt találtak rád, nem valószínû, hogy máshol el tudsz majd bújni. Elôbb-utóbb a szerencséd is elfogy.";
			link.l1.go = "BetsiPrice_5";
		break;

		case "BetsiPrice_5":
			dialog.text = "Mit javasolsz? Csak add oda neki az iratokat, és maradj üres kézzel? Azok után, amin keresztülmentem?";
			link.l1 = "Ugye tudod, hogy számukra te csak egy probléma vagy, amit meg kell szüntetni. Nem fognak leállni, amíg meg nem kapják, amit akarnak. De még mindig van választásod. Add oda az iratokat annak az idiótának. Hagyd, hogy átadja ôket a gazdájának, és biztosítsd arról, hogy feladtad a szándékaidat, és egyszerûen csak azt akarod, hogy ennek az egésznek vége legyen.";
			link.l1.go = "BetsiPrice_6";
		break;

		case "BetsiPrice_6":
			dialog.text = "Ha ez az egyetlen esélyem... Rendben, kész vagyok vállalni a kockázatot. Mindig magamnál tartottam az iratokat. Belevarrtam ôket a fûzômbe, hogy egy pillanatra se szakadjak el tôlük. Várjon, csak egy pillanat...";
			link.l1 = "...";
			link.l1.go = "BetsiPrice_7";
		break;

		case "BetsiPrice_7":
			dialog.text = "Tessék, fogd meg. Ez az összes irat, ami nálam volt. Mondana néhány búcsúszót annak a lénynek? Tudja, hogy kell meggyôzônek lenni, ugye?";
			link.l1 = "Azt hiszem, már megtanulta a legfontosabb leckét. Most már csak azt kell tisztáznunk vele, hogy mit kell tennie.";
			link.l1.go = "exit";
			notification(StringFromKey("Neutral_15"), "BoxMinus");
			PlaySound("interface\\important_item.wav");
			AddDialogExitQuestFunction("TBP_HouseBetsi_11");
		break;
		
		case "Pirate_6":
			dialog.text = "...";
			link.l1 = "Álljon fel. És jól figyelj rám, te szemétláda. Itt vannak a dokumentumok, amikért küldtek. Vidd el ôket a gazdádnak, és mondd meg neki: ha továbbra is gyilkosokat küld Betsy után, ugyanarra a sorsra jutnak, mint a barátaid. Mondd meg neki, hogy a lány örökre távozik az életébôl - és nincs többé oka arra, hogy üldözze. Hadd tekintse ezt a megbékélés felé tett önkéntes lépésének. Remélem, lesz elég józan ahhoz, hogy ez itt véget érjen. Mindent megértettél, vagy ezt az információt nekem kell a fejedbe vernem?";
			link.l1.go = "Pirate_7";
			notification(StringFromKey("Neutral_16"), "BoxMinus");
			PlaySound("interface\\important_item.wav");
		break;

		case "Pirate_7":
			dialog.text = "Mindent megértettem, "+GetAddress_Form(NPChar)+"...";
			link.l1 = "Akkor tûnj el innen. És eszedbe se jusson itt maradni - ha még egyszer meglátlak itt, nem kapsz második esélyt.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_12");
		break;

		case "BetsiPrice_8":
			dialog.text = "Nos, "+GetSexPhrase("hôsöm","dühöm")+", úgy tûnik, még köszönetet is elfelejtettem mondani... Az egész az izgalom miatt van. Nem mindennap fordul elô, hogy az ember fogságban találja magát, majd visszanyeri szabadságát egy ilyen bátor "+GetSexPhrase("megmentônek","megmentônônek")+"köszönhetôen. Mondd csak, ez a szokásod - megmenteni a hölgyeket a bajból, vagy csak hihetetlenül szerencsés vagyok?";
			link.l1 = "Mit mondhatnék, Betsy, gyengém a drámai belépôk és "+GetSexPhrase("gyönyörû hölgyek","mindenféle kalandok")+".";
			link.l1.go = "BetsiPrice_9";
		break;

		case "BetsiPrice_9":
			dialog.text = "A nevem Miranda. Miranda Bell. A Betsy nevet vettem fel, amikor el kellett tûnnöm - új élet, új név, érted. Olyan sietve menekültem el Európából, hogy csak néhány érmét és néhány ékszert ragadtam meg\nA többi valószínûleg azokhoz a szemetekhez került, akik vadásztak rám. Most fényûzô fogadások és drága ruhák helyett - egy nyomorult viskó a külvárosban és munka egy kocsmában. Soha nem gondoltam volna, hogy egy nap jó társaságban borízlelés helyett rumot fogok felszolgálni...";
			link.l1 = "Még mindezek ellenére is úgy nézel ki, mintha a sorsot tartanád a kezedben. Talán ebben rejlik az igazi tehetséged.";
			link.l1.go = "BetsiPrice_10";
		break;

		case "BetsiPrice_10":
			dialog.text = ""+GetSexPhrase("Hízelgô. De tudod, jól áll neked","Te hízelegsz nekem")+"... Mindezek után kissé nyugtalan vagyok. Mi van, ha már várnak rám a sarkon túl? Kísérj haza, légy az én "+GetSexPhrase("megmentôm","megmentônôm")+" még egy kis ideig.";
			link.l1 = "Nem vagyok az a fajta, aki félbehagyja a dolgokat. Szóval, asszonyom, állok szolgálatára. Gyerünk, menjünk.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma");
		break;

		case "BetsiPrice_11":
			dialog.text = "Itt is vagyunk. Tudod, még csak meg sem kérdeztem, hogy milyen szél hozott téged abba a házba?";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulonOtdatBetsy") && pchar.questTemp.TBP_BuyKulonOtdatBetsy == true)
            {
			link.l2 = "Nem véletlenül voltam ott. Ez a medál hozott oda. Vedd el. A kocsmáros nagyon feldúltnak tûnt az eltûnésed miatt, és megkért, hogy derítsem ki, mi történt. Nos, volt más választásom, hogy visszautasítsam? Egy bajba jutott hölgyet elhagyni egy kapitányhoz méltatlan cselekedet.";
			link.l2.go = "BetsiPrice_12_otdal_kulon";
			}
			else
			{
			link.l1 = "Nem véletlenül voltam ott. A kocsmáros úgy tûnt, komolyan felzaklatta az eltûnése, és megkért, hogy derítsem ki, mi történt. Nos, volt más választásom, hogy visszautasítsam? Egy bajba jutott hölgyet elhagyni egy kapitányhoz méltatlan cselekedet.";
			link.l1.go = "BetsiPrice_12";
			}
		break;
		
		case "BetsiPrice_12":
			dialog.text = "Ah, ez olyan nemes, kapitány "+pchar.name+"! Bár biztos vagyok benne, hogy a kocsmáros jobban aggódott a profitja miatt, mint miattam. Sajnos, ma nem hívhatlak be - helyre kell jönnöm. A pincében töltött idô aligha tett szebbé. De ha nem látjuk egymást többé - ezt nem bocsátom meg neked. Úgyhogy gyere el holnap a kocsmába, lesz egy... ajándékom számodra.";
			link.l1 = "Nos, most már van egy újabb okom, hogy beugorjak. Viszlát, M... Betsy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_3");
		break;
		
		case "BetsiPrice_12_otdal_kulon":
			dialog.text = "Ah, ez olyan nemes, kapitány "+pchar.name+"! Bár biztos vagyok benne, hogy a kocsmáros jobban aggódott a profitja miatt, mint miattam. Sajnos, ma nem hívhatlak be - helyre kell jönnöm. A pincében töltött idô aligha tett szebbé. De ha nem látjuk egymást többé - ezt nem bocsátom meg neked. Úgyhogy gyere el holnap a kocsmába, lesz egy... ajándékom számodra.";
			link.l1 = "Nos, most már van egy újabb okom, hogy beugorjak. Viszlát, M... Betsy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_3");
			TakeItemFromCharacter(pchar, "jewelry24");
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
		break;

		case "TBP_Helena_1":
			dialog.text = "Nocsak, nocsak... Micsoda édes búcsú. Ki ez a zilált hölgy? Úgy néz ki, mintha egy hétig egy pincében ült volna, de még ez sem akadályozott meg abban, hogy a szemeddel faljad fel, ugye, "+pchar.name+"?";
			link.l1 = "Ez nem az, amire gondoltál. A lány nehéz helyzetbe került, és én segítettem neki kijutni. Ez minden.";
			link.l1.go = "TBP_Helena_2";
		break;

		case "TBP_Helena_2":
			dialog.text = "És te, természetesen, úgy döntöttél, hogy a lovagja leszel a fényes páncélban?";
			link.l1 = "Tudod, nem maradhatok a pálya szélén, ha valaki veszélyben van.";
			link.l1.go = "TBP_Helena_3";
		break;

		case "TBP_Helena_3":
			dialog.text = "Jól van. De legközelebb, "+pchar.name+", légy óvatosabb... és ne adj okot arra, hogy féltékeny legyek.";
			link.l1 = "Persze, drágám. Menjünk innen, még sok dolgunk van.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_5");
		break;

		case "TBP_Mary_1":
			dialog.text = "Nocsak, nocsak... Milyen édes búcsú. Micsoda gondoskodás, ilyen gyengéd ígéretek... Még a nevén is szólítja, olyan gyengéden, rendben. Talán nekem is el kellene tûnnöm pár napra, hogy ugyanolyan buzgalommal keressetek?";
			link.l1 = "Mary, tudod, hogy te vagy az én talizmánom, ô pedig... csak egy lány, aki bajba került.";
			link.l1.go = "TBP_Mary_2";
		break;

		case "TBP_Mary_2":
			dialog.text = "Á, hát persze! Csak egy szerencsétlen, akinek szüksége van egy lovagra! És az a tekinteted - az is csak udvariasságból volt? Majdnem levetkôztetted a szemeddel!";
			link.l1 = "Mary, túlzol! Nézd, hogy nézek rád? Látod a különbséget? Vagy emlékeztetnem kell téged... közelrôl?";
			link.l1.go = "TBP_Mary_3";
		break;

		case "TBP_Mary_3":
			dialog.text = "Jól van, "+pchar.name+", ezúttal jól kibújtál belôle, rendben. De ha még egyszer látok egy ilyen jelenetet...";
			link.l1 = "Akkor újra emlékeztetnem kell téged, hogy ki az elsô és egyetlen hely a szívemben. Gyere, drágám, még sok dolgunk van.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_5");
		break;
		
		case "BetsiPrice_sex_1":

			switch (rand(1))
			{
				case 0:
					dialog.text = "Mmm... El sem tudod képzelni, milyen gondolatok járnak a fejemben, amikor ilyen közel vagyok hozzád... És hogy mennyire szeretném ôket valóra váltani.";
					link.l1 = "Akkor hagyd abba a gondolkodást... és mutasd meg nekem mindegyiket.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "Ah, kedves"+GetSexPhrase("","")+"... fogalmad sincs, milyen nehéz nekem uralkodni magamon, amikor a közeledben vagy...";
					link.l1 = "Akkor elég ebbôl az édes kínzásból... Gyere hozzám...";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
			AddDialogExitQuestFunction("TBP_Betsi_sex_3");
		break;

		case "BetsiPrice_sex_2":
			switch (rand(1))
			{
				case 0:
					dialog.text = "Ah, "+GetSexPhrase("édes kapitányom","édes "+pchar.name+"")+"... Még mindig benne vagyok ebben az édes ôrületben.";
					link.l1 = "Talán érdemes emlékezni erre az ôrületre... vagy akár megismételni egy nap.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "Ó, "+pchar.name+"... Ha azt mondom, hogy csodálatos volt, akkor nem fogod túlságosan elszállni"+GetSexPhrase(", ugye?",". ugye?")+"?";
					link.l1 = "Csak ha megígéred, hogy még egyszer elmondod... suttogva.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
			AddDialogExitQuestFunction("TBP_Betsi_sex_7");
		break;

		
		
		
		
		
		
		
	}
}