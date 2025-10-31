void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
			dialog.text = "Mit akarsz?";
			link.l1 = "Semmi.";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Alamida_church":
			dialog.text = "...és a Szentlélek. Ámen.";
			link.l1 = "Ritkán látok katonákat templomokban.";
			link.l1.go = "Alamida_church_2";
		break;
		
		case "Alamida_church_2":
			dialog.text = "Sokan úgy gondolják, hogy a hit és a kard összeegyeztethetetlen. De egy sebész nem azért vág, hogy gyógyítson? Egy apa nem azért büntet, hogy megvédjen?";
			link.l1 = "Ez úgy hangzik, mint a megigazulás.";
			link.l1.go = "Alamida_church_3";
			link.l2 = "Ebben van bölcsesség. Néha a kegyetlenségre szükség van.";
			link.l2.go = "Alamida_church_4";
		break;
		
		case "Alamida_church_3":
			dialog.text = "You're mistaken. Ez nem igazolás - ez megértés. Amikor elkezdtem a szolgálatomat, minden egyes haláleset... nehéz volt. De aztán... kinyílt a szemem. 'A kegyetlenség a legfôbb szeretet megnyilvánulása.";
			link.l1 = "Magatokra hagylak benneteket az imáitokkal.";
			link.l1.go = "Alamida_church_5";
		break;
		
		case "Alamida_church_4":
			dialog.text = "Igen... igen! Pontosan ezt'mondta, az, aki erre az útra vezetett engem. 'A szánalom erô nélkül haszontalan, mint a kard kéz nélkül.";
			link.l1 = "Magatokra hagylak benneteket az imáitokkal.";
			link.l1.go = "Alamida_church_5";
		break;
		
		case "Alamida_church_5":
			dialog.text = "Imádkozzatok mindannyiunkért. Azért, amit teszünk... és amit még tennünk kell.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_guber":
			dialog.text = "Hét százalékos hiány. Legutóbb öt volt. Úgy nônek, mint a gaz egy elhagyatott kertben...";
			link.l1 = "Új kormányzó van a városban?";
			link.l1.go = "Alamida_guber_2";
		break;
		
		case "Alamida_guber_2":
			dialog.text = "Micsoda? Á, nem. Ôexcellenciája ott van a sarokban. Don Fernando de Alamida vagyok, királyi felügyelô.";
			link.l1 = "Nehéz munka lehet.";
			link.l1.go = "Alamida_guber_3";
		break;
		
		case "Alamida_guber_3":
			dialog.text = "Tudja, mi a legnehezebb a korrupció elleni harcban? A bûnösök nem feltétlenül rossz emberek. Gyerekeik vannak, családjuk. És minden alkalommal emlékeztetned kell magad: a méreg akkor is méreg marad, ha aranypohárban tálalják.";
			link.l1 = "De lehet-e ilyen szigorúan ítélkezni? Mindannyian emberek vagyunk...";
			link.l1.go = "Alamida_guber_4";
			link.l2 = "Túl puhány vagy. Csak a börtön fogja megjavítani ôket.";
			link.l2.go = "Alamida_guber_5";
		break;
		
		case "Alamida_guber_4":
			dialog.text = "A farkasnak való kegyelem kegyetlenség a báránynak. Ezt mondta... egy bölcs ember. És minden egyes nappal egyre jobban megértem a bölcsességét.";
			link.l1 = "Nem vonom el tovább a figyelmét a munkájától.";
			link.l1.go = "Alamida_guber_6";
		break;
		
		case "Alamida_guber_5":
			dialog.text = "Hm. Tudja, én is így gondoltam. De a börtön túl egyszerû. Valami többre van szükség... Megtisztulás.";
			link.l1 = "Nem vonom el tovább a figyelmét a munkájától.";
			link.l1.go = "Alamida_guber_6";
		break;
		
		case "Alamida_guber_6":
			dialog.text = "Igen. A papírok nem várnak. Bár néha úgy érzem, hogy itt minden szám mögött valaki sorsa rejtôzik.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_city":
			dialog.text = "Figyelmesen hallgatom, "+GetAddress_Form(NPChar)+"? Mi késztetett arra, hogy csak így, az utcán közeledj hozzám?";
			link.l1 = "Maga kiemelkedik a többiek közül.";
			link.l1.go = "Alamida_city_2";
		break;
		
		case "Alamida_city_2":
			dialog.text = "Don Fernando de Alamida, királyi felügyelô. Maga az elsô ilyen kíváncsi ma. Mindenki elbújik, mindenki fél tôlem. Pedig egy becsületes embernek nincs mitôl félnie. Mit mond ez nekünk?";
			link.l1 = "Hogy a hírneve megrémíti ôket?";
			link.l1.go = "Alamida_city_3";
			link.l2 = "Hogy kevés az ôszinte ember?";
			link.l2.go = "Alamida_city_4";
		break;
		
		case "Alamida_city_3":
			dialog.text = "Mulatságos. Én is így gondoltam. Amíg meg nem értettem - a félelem megtisztít. Ha valaki fél, ôszintébbé válik. Közelebb kerül a valódi természetéhez. Istenhez.";
			link.l1 = "Érdekes gondolat. Mennem kell. Jó napot, don Fernando.";
			link.l1.go = "Alamida_city_5";
		break;
		
		case "Alamida_city_4":
			dialog.text = "Érdekes... Úgy gondolkodik, mint egy ismerôsöm. Kár, hogy nem mindenki tudja elfogadni ezt az igazságot.";
			link.l1 = "Érdekes gondolat. Mennem kell. Jó napot, don Fernando.";
			link.l1.go = "Alamida_city_5";
		break;
		
		case "Alamida_city_5":
			dialog.text = "Jól van? Igen, talán. Amíg ez igazságos.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_exit":
			DialogExit();
			AddDialogExitQuestFunction("SantaMisericordia_Alamida_DlgExit");
		break;
		
		case "Alamida_repeat":
			dialog.text = "Még valami, kapitány?";
			link.l1 = "Nem, don Fernando, csak üdvözlöm, semmi több.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alamida_repeat";
		break;
		
		case "Alamida_abordage":
			if (startHeroType == 4)
			{
				dialog.text = "Egy kardos leány? Soha nem gondoltam volna, hogy megérek egy ilyen látványt. És ki lehetsz te, senorita, hogy meg mered támadni a 'Holy Mercy'?";
				link.l1 = "Hellen McArthur kapitány. És a meglepettséget az arcán jól ismerem.";
				link.l1.go = "Alamida_HelenaCaptain";
			}
			else
			{
				dialog.text = "Hogy merészeled?! Attack the 'Holy Mercy'?! A hajó, amely a király akaratát hordozza és... Nos... Ha már itt vagy, mondd meg - miért? Miért választottad ezt az ôrületet?";
				link.l1 = "Kalóz vagyok. És a gályád biztosan tele van kincsekkel.";
				link.l1.go = "Alamida_abordage_Gold";
				link.l2 = "Milyen gyönyörû hajó... Meg kell szereznem.";
				link.l2.go = "Alamida_abordage_Ship";
				link.l3 = "Az országod ellensége vagyok, don Fernando.";
				link.l3.go = "Alamida_abordage_Hater";
				link.l4 = "Csak azért. Miért ne?";
				link.l4.go = "Alamida_abordage_Prikol";
			}
		break;
		
		case "Alamida_HelenaCaptain":
			dialog.text = "Hogy hasonlítasz Szûz Máriára, a hajónk védelmezôjére... Épp olyan gyönyörû. De ô az igazakat védi, míg te...";
			link.l1 = "A hajójáért jöttem. És a bókok itt nem segítenek, don Fernando.";
			link.l1.go = "Alamida_HelenaCaptain_2";
		break;
		
		case "Alamida_HelenaCaptain_2":
			dialog.text = "Milyen szomorú. Akkor alázatra kell tanítanom téged. Erôszakkal, mivel nincs más lehetôség.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Gold":
			dialog.text = "Á, igen. Hát persze. Arany. Mindig arany. A méreg, ami megrágja a lelkeket. Ezért meg fogsz halni.";
			link.l1 = "Ne légy ilyen drámai. Ez csak üzlet.";
			link.l1.go = "Alamida_abordage_Gold_2";
		break;
		
		case "Alamida_abordage_Gold_2":
			dialog.text = "Minden érme a raktérben a bûnösök' fizetés a megtisztulásért. Akarod? Akkor osztozz a sorsukban.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Ship":
			dialog.text = "Sokan áhították a 'Szent Irgalmasság'. szépségét sok kapitány végzete.";
			link.l1 = "Akkor én leszek az elsô, aki igényt tart rá.";
			link.l1.go = "Alamida_abordage_Ship_2";
		break;
		
		case "Alamida_abordage_Ship_2":
			dialog.text = "A kegyelem erô nélkül haszontalan, mint a kard kéz nélkül. Ezt a leckét ma meg kell tanulnod.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Hater":
			dialog.text = "Ennyi volt. Egy újabb féltékeny a Birodalom nagyságára.";
			link.l1 = "Milyen nagyságra? A merevséged visszatartja ezt a világot.";
			link.l1.go = "Alamida_abordage_Hater_2";
		break;
		
		case "Alamida_abordage_Hater_2":
			dialog.text = "Ne hazudj magadnak. A spanyoloktól való félelem ôszintébbé tesz. Közelebb az igazi természetedhez. Most már magad is látni fogod.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Prikol":
			dialog.text = "Ôrült. Vagy talán tesztnek küldtek hozzám?";
			link.l1 = "Nem mindenhez kell ok, senor.";
			link.l1.go = "Alamida_abordage_Prikol_2";
		break;
		
		case "Alamida_abordage_Prikol_2":
			dialog.text = "Azt mondta, hogy a magafajta emberek a legveszélyesebbek. De ez csak megerôsít a harcban.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_SecondRound":
			DialogExit();
			AddDialogExitQuestFunction("SantaMisericordia_Alamida_Abordage_DlgExit_1");
		break;
		
		case "Alamida_abordage_TrirdRound":
			if (startHeroType == 4)
			{
				dialog.text = "Micsoda lelkierô... Micsoda akarat...";
				link.l1 = "Meglepôdtél?";
			}
			else
			{
				dialog.text = "Nem rossz. Régen találkoztam már méltó ellenféllel.";
				link.l1 = "Nem hagyok neked idôt pihenni.";
			}
			link.l1.go = "Alamida_abordage_TrirdRound_2";
		break;
		
		case "Alamida_abordage_TrirdRound_2":
			if (startHeroType == 4)
			{
				dialog.text = "Figyelmeztettek... egy ilyen próbára. Olyan szépségrôl, ami megingathatja egy harcos hitét.";
				link.l1 = "Mindig ennyire bonyolítja az egyszerû dolgokat, don Fernando?";
			}
			else
			{
				dialog.text = "Az Úr erôt ad azoknak, akik az igaz ügyet szolgálják. Bár... néha már nem vagyok benne biztos, hogy mit is szolgálok.";
				link.l1 = "Kétségeid vannak?";
			}
			link.l1.go = "Alamida_abordage_TrirdRound_3";
		break;
		
		case "Alamida_abordage_TrirdRound_3":
			if (startHeroType == 4)
			{
				dialog.text = "Egyszerû? Nem... Kell lennie valami magasabb értelemnek. Ez egy próba. Nem tévedhetek.";
			}
			else
			{
				dialog.text = "Nem. Ô tanított meg, hogy ne kételkedjek. Soha.";
			}
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_TrirdRound_4";
		break;
		
		case "Alamida_abordage_TrirdRound_4":
			DialogExit();
			AddDialogExitQuestFunction("SantaMisericordia_Alamida_Abordage_DlgExit_2");
		break;
		
		case "Alamida_abordage_Molitva":
			dialog.text = "Várjatok... Várj. Te nyertél. Megsebesültem, elvéreztem. Hadd imádkozzak a halál elôtt.";
			link.l1 = "Rendben.";
			link.l1.go = "Alamida_abordage_Molitva_2";
		break;
		
		case "Alamida_abordage_Molitva_2":
			if (startHeroType == 4)
			{
				dialog.text = "Uram... bocsásd meg bûneimet, és adj erôt a megpróbáltatás eme órájában. Áldd meg elesett bajtársaim lelkét. Hûséges tengerészek, abban a hitben haltak meg, hogy igazságot hordoznak\nApa, igyekeztem tanításaid szerint élni, harcolni az igazságtalanság ellen. De a fiad bemocskolta az Alamida család becsületét. Forgive me\nMotherland... Megesküdtem, hogy hûségesen és ôszintén szolgállak téged. De a buzgalmam, a haragom... Azzá váltam, ami ellen harcolni akartam\nDiego... Talán hazudott? Egész idô alatt... Jaj nekem, ha így van\nÉs áldd meg ezt a nôt, Uram. Talán végsô kegyelmedben küldted ôt hozzám... hogy lássam, milyen messzire tévedtem. Ámen.";
			}
			else
			{
				dialog.text = "Uram... bocsásd meg bûneimet, és adj erôt a megpróbáltatás eme órájában. Áldd meg elesett bajtársaim lelkét. Hûséges tengerészek, abban a hitben haltak meg, hogy igazságot hordoznak\nApa, igyekeztem tanításaid szerint élni, harcolni az igazságtalanság ellen. De a fiad bemocskolta az Alamida család becsületét. Forgive me\nMotherland... Megesküdtem, hogy hûségesen és ôszintén szolgállak téged. De a buzgalmam, a haragom... Azzá váltam, ami ellen harcolni akartam\nDiego... Talán hazudott? Egész idô alatt... Jaj nekem, ha így van\nSzent Szûz Mária, imádkozz értünk Istenhez, és add meg nekünk kegyelmedet. Ámen.";
			}
			link.l1 = "Nem ismerlek meg, don Fernando. Úgy nézel ki, mint egy másik ember. És kirôl beszéltél?";
			link.l1.go = "Alamida_abordage_Molitva_3";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "Church_Stay_1", "", 5.0);
		break;
		
		case "Alamida_BitvaEnd":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "SantaMisericordia_CanLeaveCauta", 5);
		break;
			
		case "Alamida_abordage_Molitva_3":
			DialogExit();
			AddDialogExitQuestFunction("SantaMisericordia_Alamida_Abordage_DlgExit_3");
		break;
		
		//Элен
		case "Alamida_Helena":
			dialog.text = "Kapitányom, gratulálok! Micsoda ádáz csata. Az a kapitány ügyes volt, nagyon ügyes. De te... te még jobbnak bizonyultál. Milyen büszke vagyok rád...";
			link.l1 = "Köszönöm, szerelmem. Megsérültél?";
			link.l1.go = "Alamida_Helena_2";
		break;
		
		case "Alamida_Helena_2":
			dialog.text = "Nem, nem, nem. Bár azt hittem, hogy néhányszor a határon voltunk - a beszállás elôtt és közben is. És te, jól vagy?";
			link.l1 = "Jól vagyok, még egyszer köszönöm. Pihenjen a kabinban, hamarosan csatlakozom.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Мэри
		case "Alamida_Mary":
			dialog.text = "Charles, jól vagy? Jöttem, amint tudtam, rendben.";
			link.l1 = "Jól vagyok, köszönöm, drágám. Bár elég nehéz volt.";
			link.l1.go = "Alamida_Mary_2";
		break;
		
		case "Alamida_Mary_2":
			dialog.text = "Örülök! De... Figyelj, Charles? Miért támadtuk meg ezeket az embereket? Az Úr nem fogja ezt megbocsátani nekünk, nem. Ez a hajó... mint egy nagy templom. Amikor megláttam, megremegett a szívem, mint amikor elôször láttam egy igazi templomot, nem csak a könyvekben. És most vérzik!";
			link.l1 = "Mary... Tudod, hogy a látszat néha csal. És a jámborság álarca mögött ott voltak azok, akik pénzt vettek el az egyszerû hívôktôl - akárcsak te. Érted?";
			link.l1.go = "Alamida_Mary_3";
		break;
		
		case "Alamida_Mary_3":
			dialog.text = "I... Hiszek neked, Charles. Rendben van. Csak... legalább az itt talált arany egy részét adományozzuk azoknak, akiknek valóban szükségük van rá? Megkönnyítené a szívemet.";
			link.l1 = "Megtesszük, Mary. Megígérem. Most pedig szedd össze a gondolataidat és próbálj megnyugodni. Vége van.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Томми
		case "Alamida_Tommi":
			dialog.text = "Gratulálok a gyôzelméhez, kapitány! Na ezt nevezem én üzletnek! Micsoda fogás ezen a gályán!...";
			link.l1 = "Ma még szélesebb a vigyorod, mint máskor, Tommy.";
			link.l1.go = "Alamida_Tommi_2";
		break;
		
		case "Alamida_Tommi_2":
			dialog.text = "Hát persze! Micsoda kényeztetés. És micsoda harc. A forradalomra emlékeztetett. És még... heh.";
			link.l1 = "Mi az, Tommy? Gyerünk, beszélj.";
			link.l1.go = "Alamida_Tommi_3";
		break;
		
		case "Alamida_Tommi_3":
			dialog.text = "Hogy feldíszítették az egész hajót, mint egy úszó katedrálist. És mennyi aranyat gyûjtöttek össze mindenhonnan. Igazi pápista szentek! Szégyen és nevetséges.";
			link.l1 = "Ez egy kincstári hajó, Tommy. Nem egy templomhajó.";
			link.l1.go = "Alamida_Tommi_4";
		break;
		
		case "Alamida_Tommi_4":
			dialog.text = "A mi esetünkben nincs nagy különbség. Akárhogy is, örültem, hogy jól megleckéztettem azokat a dónokat és pápistákat! Ki nem állhatom egyiküket sem. Nagyon élveztem ezt a napot, ha-ha-ha-ha!";
			link.l1 = "Te sosem változol! Rendben, leléphet. Itt minden rendben van.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Тичингиту
		case "Alamida_Tichingitu":
			if (startHeroType == 1)
			{
				dialog.text = "Charles kapitány, gyôzelmet aratunk. Ez nehéz harc lesz. Még Tichingitu is nehéznek találja, pedig én vagyok az egyik legjobb harcos a faluban.";
				link.l1 = "Ez igaz, barátom. Valóban méltó ellenfelek voltak.";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Senor de Montoya, a hajó a miénk.";
				link.l1 = "Nagyon jó, Tichingitu. Én is most végeztem itt.";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Paterson kapitány, az utolsó ellenállást is leverték a hajón.";
				link.l1 = "Elkéstél, Tich! Legközelebb jobb, ha velem maradsz. Nem mintha egyedül nem tudnék megbirkózni vele...";
			}
			if (startHeroType == 4)
			{
				dialog.text = "McArthur kapitány, jól van?";
				link.l1 = "Igen, Tichingitu, jól vagyok, köszönöm, hogy megkérdezted. És ne kételkedj a kapitányodban - egyedül is tökéletesen megbirkóztam vele.";
			}
			link.l1.go = "Alamida_Tichingitu_2";
		break;
		
		case "Alamida_Tichingitu_2":
			if (startHeroType == 1)
			{
				dialog.text = "A szellemek ezt mondják nekem harc közben. És megkérdezik, hogy miért én öltem meg ôket. Most én kérdezem ugyanezt tôled. Tichingitu látja a szemükben, hogy nem gonosztevôk. Még nem.";
				link.l1 = "Ah, mit mondhatnék neked? Nincs válaszom, Tichingitu.";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Én akarok kérdezni tôled, de Montoya kapitány.";
				link.l1 = "Hallgatlak.";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Tichingitu kérdezni akarok tôled valamit, William kapitány, ha megengeded.";
				link.l1 = "Megadva.";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Én nem kételkedem, aggódom önért, kapitány.";
				link.l1 = "Rendben, rendben. Látom a szemedben, hogy valami mást akarsz kérdezni.";
			}
			link.l1.go = "Alamida_Tichingitu_3";
		break;
		
		case "Alamida_Tichingitu_3":
			if (startHeroType == 1)
			{
				dialog.text = "Hmm, ahogy mondod, kapitány. Befejezzük itt?";
				link.l1 = "Igen. Körülnézek még egy kicsit, aztán csatlakozom a többiekhez.";
				link.l1.go = "Alamida_BitvaEnd";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Ezek az emberek nem ugyanabból a törzsbôl származnak, mint te? Nem spanyolok? Miért döntöttél úgy, hogy megtámadsz?";
				link.l1 = "Ez igaz. De az indián törzsek nem harcolnak egymással? Vagy nincsenek veszekedések és viszályok egy törzsön belül?";
				link.l1.go = "Alamida_Tichingitu_4";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Ez a hajó úgy néz ki, mint egy templom. Utálod a templomot és a fehér istent?";
				link.l1 = "Egyáltalán nem. De ez csak dekoráció, érted? Ez egy kincstári hajó. Bár nem értheted - úgy hallottam, a te néped azt sem tudja, mi az adó. Szerencsés ördögök.";
				link.l1.go = "Alamida_Tichingitu_4";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Igen. Légy igaz. MacArthur kapitány, miért támadjuk meg ezt az úszó templomot?";
				link.l1 = "Lebegô templom, ha-ha-ha-ha! Nem, nem, nem, nem, nem, nem, nem, nem, nem, nem, nem, nem, nem. Ez egy kincstári hajó. Hmm, látom, nem egészen érti. Nos, aranyat szállítottak. El tudom képzelni, milyen büszke lesz Jan, amikor elmondom neki, hogy legyôztem Fernando de Alamidát!";
				link.l1.go = "Alamida_Tichingitu_4";
			}
		break;
		
		case "Alamida_Tichingitu_4":
			if (startHeroType == 2)
			{
				dialog.text = "Hmm, igaza van, kapitány. De az indiánokkal ez kevésbé történik meg, mint a fehérekkel.";
				link.l1 = "Talán. Nos, ez az ember... belém kötött.";
				link.l1.go = "Alamida_Tichingitu_5";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Igazad van, a maszkogiknak nincsenek kastélyaik és adójuk.";
				link.l1 = "Pontosan. Elmehetsz, úgyis elkéstél. Majd késôbb eldöntjük, hogy mi legyen ezzel a gyönyörû gályával. Nem szeretem ezeket a kádakat, de a fenébe is, ez egy szépség.";
				link.l1.go = "Alamida_BitvaEnd";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Tichingitu is büszke rád, kapitány. És gratulálok a gyôzelemhez ebben a kemény küzdelemben.";
				link.l1 = "Köszönöm. Most pedig osszuk fel a zsákmányt.";
				link.l1.go = "Alamida_BitvaEnd";
			}
		break;
		
		case "Alamida_Tichingitu_5":
			dialog.text = "Közbelép, Senor de Montoya?";
			link.l1 = "Pontosan. Ez a szigetvilág túl kicsi mindkettônknek. És én sokkal hasznosabb vagyok az államunk számára. Emlékezz Kakaólevélre - több kárt okozott a testvéreinek, mint hasznot. Ugyanez a helyzet itt is.";
			link.l1.go = "Alamida_Tichingitu_6";
		break;
		
		case "Alamida_Tichingitu_6":
			dialog.text = "Most már értem. Tichingitu elmehet, kapitány?";
			link.l1 = "Igen, mehet. Én is hamarosan csatlakozom hozzátok.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			dialog.text = LinkRandPhrase("Hé, mi ez a sok fegyverforgatás?! Azonnal tedd el!", "Megparancsolom, hogy azonnal tegye el a fegyverét!", "Hé, " + GetAddress_Form(NPChar) + ", ne ijesztgesse az embereket! Tegye el a fegyvert!");
			link.l1 = LinkRandPhrase("Rendben, elrakom...", "Már megtettem.", "Ahogy mondod...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Cseszd meg!", "Azt hiszem, használni fogom!", "Majd elrakom, ha eljön az ideje.");
			link.l2.go = "fight";
		break;
		
	}
} 