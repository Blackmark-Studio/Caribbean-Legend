// Хосе Диос - картограф
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Akarsz valamit?";
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "dios")
			{
				link.l3 = TimeGreeting()+"! Mondd csak, te vagy Jose Dios, a térképész?";
				link.l3.go = "island";
			}
			link.l1 = "Nem, semmit.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;
		
		case "island":
			dialog.text = "Igen, én vagyok. Nem ismerem magát, senor. Mit akar tôlem?";
			link.l1 = "A nevem "+GetFullName(pchar)+" , és Jan Svenson küldött. Emlékszel rá?";
			link.l1.go = "island_1";
		break;
		
		case "island_1":
			dialog.text = "Á, Svenson úr! Persze, hogy emlékszem rá! Jöjjön, helyezze magát kényelembe... Hogy van a tisztelt Jan?";
			link.l1 = "Köszönöm, jól van. Senor Dios, szükségem van a segítségére. Egy olyan ügyben szeretnék önnel konzultálni, amit a szakmája miatt biztosan ismer. Jan ajánlotta önt, mint a karibi térség földrajz szakértôjét...";
			link.l1.go = "island_2";
		break;
		
		case "island_2":
			dialog.text = "Hallgatom, Senor. Mit szeretne tudni a szigetcsoport földrajzáról?";
			link.l1 = "Azt mondják, hogy Havannától északnyugatra, Kuba és a Mexikói-öböl között van egy sziget vagy valamilyen más képzôdmény. Ezt a szigetet még soha nem tüntették fel semmilyen térképen. Szeretném tudni, mennyire megbízhatóak ezek a pletykák.";
			link.l1.go = "island_3";
		break;
		
		case "island_3":
			dialog.text = "Hm... Ön olyasmirôl kérdezett, ami már évek óta foglalkoztat. Ez a hely, amit említett, már régóta vonzza a geográfusok kíváncsi elméit, de még senki sem volt elég bátor ahhoz, hogy felfedezze ezt a régiót.";
			link.l1 = "Miért?";
			link.l1.go = "island_4";
		break;
		
		case "island_4":
			dialog.text = "Az a helyzet, hogy ez a hely valamiféle természeti anomália. A viharok valószínûsége abban a régióban sokkal nagyobb, mint bárhol máshol. Talán a hideg tengeráramlásban rejlik az ok, de ez csak az én hipotézisem. Sok hajó tûnt el ott, és ez elég volt ahhoz, hogy a hajósok elkerüljék azt a helyet, az összes fô tengeri útvonal amúgy is messze halad el attól a régiótól.";
			link.l1 = "Gondolom, te sem tudod az igazságot...";
			link.l1.go = "island_5";
		break;
		
		case "island_5":
			dialog.text = "Pontosan, Senor. De van néhány történelmi dokumentumom és néhány tárgyi bizonyítékom, így minden jogom megvan ahhoz, hogy nagy valószínûséggel gyanítsam annak a helynek a létezését.";
			link.l1 = "Tudna többet mondani?";
			link.l1.go = "island_6";
		break;
		
		case "island_6":
			dialog.text = "Persze. A legfontosabb bizonyíték az a történelmi dokumentum, amely kivonatokat tartalmaz Alvarado kapitány naplójából, aki 1620-ban járt a szigeten. Elég érdekes történet, mondom én!";
			link.l1 = "Alvarado kapitány? Már másodszor hallom ezt a nevet...";
			link.l1.go = "island_7";
		break;
		
		case "island_7":
			dialog.text = "Nem vagyok meglepve. Alvarado kapitány története évek óta a folklór része. Változott, tele lett pletykákkal, hazugságokkal és álmokkal, így hát itt van - az Elhagyott hajók szigetének legendája.\nA pletyka változhat, de a papír és a tinta nem, az évszázadokon át megmarad. Tessék, olvassa el ezt a történetet - talán segít feltárni, amit keres.";
			link.l1 = "Köszönöm! Van még valami?";
			link.l1.go = "island_8";
		break;
		
		case "island_8":
			dialog.text = "Van egy elmélet, amely szerint a tengerfenék ezen a területen elég magasra emelkedik ahhoz, hogy egy hatalmas zátony alakuljon ki. És már említettem az áramlatot. A tengerészek szerint a sirályok és más tengeri madarak is nagy számban gyûlnek itt össze' talks.\nAlvorado olyan hajók neveit említette, amelyek Francisco Betancourt admirális hajórajához tartoztak, egy olyan hajórajhoz, amely több mint ötven évvel ezelôtt veszett oda. Kétlem, hogy ez csak véletlen egybeesés lenne...";
			link.l1 = "Visszatérek a hajómra, és figyelmesen elolvasom Alvarado feljegyzéseit. Köszönöm a segítségét, Senor Dios!";
			link.l1.go = "island_9";
		break;
		
		case "island_9":
			dialog.text = "Szívesen. Igazából egyáltalán nem segítettem neked, neked sincsenek meg a hely koordinátái, és nekem sincsenek. Még azt sem tudom bizonyítani, hogy van odakint egy lakott sziget. De ha jól értem, szándékodban áll felfedezni ezt a területet?\nHa így van, akkor tudd, hogy nagyon hálás leszek minden információért, fôleg, ha tárgyi bizonyítékkal is ellátnak. Úgy tûnik, hogy ön egy gazdag ember, de meg fogom találni a módját, hogy visszafizessem önnek.";
			link.l1 = "Köszönöm, Dios Dios. Akkor megegyeztünk, Senor Dios. Talán az én jegyzeteimet is el fogja olvasni valaki a jövôben... És valaki talán még egy legendát is ír...";
			link.l1.go = "island_10";
		break;
		
		case "island_10":
			dialog.text = "Miért nem? Senor "+pchar.name+", látom, hogy ön egy kalandvágyó ember, aki sokat utazik, ezért szeretnék megkérni valamire.";
			link.l1 = "Igen? Hallgatom.";
			link.l1.go = "island_11";
		break;
		
		case "island_11":
			dialog.text = "Tudja, hogy térképész vagyok. Tehát két éve rajzolom a karibi szigetvilág térképeit, és állítom össze az admirális atlaszát a Nueva Granada alkirályi versenyre. De mind a huszonnégy térképemet a legpimaszabb módon ellopták a házamból, miközben kalózok fogságába estem, azok, akiktôl senor Svenson megmentett.\nBiztos vagyok benne, hogy a támadást az egyik versenytársam szervezte, hogy megszerezze a térképeimet. Már régen volt, de egyetlen térképet sem láttam újra a készletembôl.";
			link.l1 = "Értem. Azt akarod, hogy visszaadjam a térképeidet.";
			link.l1.go = "island_12";
		break;
		
		case "island_12":
			dialog.text = "Pontosan. Talán a jövôbeni kalandjaid során megtalálod ôket. Könnyû felismerni ôket - a jelem rajta van mindegyiken. Nagylelkûen megjutalmazlak, ha csodával határos módon mind a huszonnégy térképet össze tudod gyûjteni.";
			link.l1 = "Rendben. Mostantól figyelmesen megnézek minden térképet, amit a szigetvilágban találok. Nos, most mennem kell. Köszönöm az érdekes beszélgetést és a dokumentumot.";
			link.l1.go = "island_13";
		break;
		
		case "island_13":
			DialogExit();
			AddQuestRecordInfo("LSC_Alvorado", "1");
			AddQuestRecord("SharkHunt", "4");
			pchar.questTemp.Saga.SharkHunt = "LSC";
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			pchar.questTemp.AdmiralMap = "true";
		break;
		
		case "Dios":
			dialog.text = "A-ah, ön az, senor "+GetFullName(pchar)+"? Van valami érdekes mondanivalója?";
			if (CheckAttribute(pchar, "questTemp.AdmiralMap") && CountAdmiralMapFromCharacter() > 0 && CountAdmiralMapFromCharacter() < 24 && !CheckAttribute(npchar, "quest.mapinfo"))
			{
				link.l3 = TimeGreeting()+"! Senor Dios, kérem, nézze meg a térképet, amit találtam. A felirat szerint ez az egyik térképed lehet.";
				link.l3.go = "map_info";
			}
			if (CheckAttribute(pchar, "questTemp.AdmiralMap") && CountAdmiralMapFromCharacter() > 23)
			{
				link.l3 = TimeGreeting()+"! Senor Dios, jó híreim vannak. Sikerült összegyûjtenem az Ön egyedi térképeinek teljes készletét, ahogyan Ön is akarta. Itt van mind a huszonnégy térkép.";
				link.l3.go = "amap";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Dios")) // был в LSC
			{
				link.l4 = TimeGreeting()+"! Igen, megvan. Ott voltam azon a misztikus helyen, amirôl beszéltünk.";
				link.l4.go = "LSC";
			}
			link.l9 = "Eddig semmi, Senor. Csak látni akartam, hogy van.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Dios";
		break;
		
		case "map_info":
			dialog.text = "Mutasd meg... (megnézi) Persze! Ez az egyik térképem az admirális atlaszához! Kapitány, nagyon kérem, hogy találja meg mindet! Megértem, hogy ez szinte lehetetlen, de mégis... Nem akarom elveszíteni a reményt.";
			link.l1 = "Ne veszítse el, Senor. Ezt a térképet megtaláltam, így van rá esély, hogy a többit is megtalálom. Még mindig a Karib-tengeren vannak.";
			link.l1.go = "map_info_1";
		break;
		
		case "map_info_1":
			dialog.text = "Az optimizmusa nagyon bátorít engem, Senor kapitány. Talán még mindig kapok egy lehetôséget, hogy megmutassam don Juan de Cordovának, ki a szigetvilág legjobb térképésze!";
			link.l1 = "Képes lesz legyôzni minden konkurens rosszindulatú ellenfelét. A térképek tényleg csodálatosak... Viszlát, Senor!";
			link.l1.go = "exit";
			npchar.quest.mapinfo = "true";
			NextDiag.TempNode = "Dios";
		break;
		
		case "amap":
			Achievment_Set("ach_CL_110");
			dialog.text = "Nem hiszek a szememnek! Tényleg megtalálta ôket? Mindet?";
			link.l1 = "Igen. Nem volt könnyű, de a szerencse végül mégis mellém állt ebben a vállalkozásban. Vegye át a térképeit – nagyszerűek, mindegyik messze felülmúlja mindazt, amit valaha láttam.";
			link.l1.go = "amap_1";
		break;
		
		case "amap_1":
			RemoveAllAdmiralMap()
			Log_Info("Átadtad az admirális teljes térképkészletét.");
			PlaySound("interface\important_item.wav");
			dialog.text = "Hihetetlen! Ez egyszerûen hihetetlen! Hogy ôszinte legyek, soha nem hittem, hogy ez a pillanat megtörténik.";
			link.l1 = "Dum spiro, spero, Senior Dios. Most már szembenézhet don Cordovával. Biztos vagyok benne, hogy nagyra fogja értékelni a tehetségét.";
			link.l1.go = "amap_2";
		break;
		
		case "amap_2":
			dialog.text = "Köszönöm, kapitány! Még fel sem fogta, milyen nagy szolgálatot tett nekem. És ahogy ígértem - megjutalmazlak. Van egy ajándékom is a számodra. Azt hiszem, mint tengerész, nagyon hasznosnak fogja találni.";
			link.l1 = "Érdeklôdöm ön iránt, Senor!";
			link.l1.go = "amap_3";
		break;
		
		case "amap_3":
			GiveItem2Character(pchar, "spyglass5"); 
			Log_Info("Kaptál egy hajótávcsövet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Tessék! Ez egy általam tervezett hajótávcsô. Egyedülálló, és sehol máshol nem fog ilyet találni. A lencséket Európában, Spanyolország legügyesebb mestere készítette. A tokját egy baráti fegyverkovács készítette. Egy speciális állvány segít a készülék irányításában bármilyen gurulás ellenére. Mindent láthatsz, amire szükséged van, legyen az egy hajó vagy egy erôd.";
			link.l1 = "Micsoda csodálatos ajándék! Köszönöm, Senor Dios.";
			link.l1.go = "amap_4";
		break;
		
		case "amap_4":
			dialog.text = "Használja, Senor kapitány. Remélem, hogy a távcsövem jó szolgálatot tesz majd önnek.";
			link.l1 = "Semmi kétség! Alig várom, hogy a hajóm fedélzetén elhelyezzem, és átnézhessek rajta.";
			link.l2.go = "amapcopy_01";
		break;
		
		case "amapcopy_01":
			AddCharacterExpToSkill(pchar, "Fortune", 1000);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 1000); // харизма
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность (раз телескоп дали)
			ChangeCharacterComplexReputation(pchar, "nobility", 10);// репутация-известность
			ChangeCharacterComplexReputation(pchar, "authority", 5);// репутация-авторитет
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			ChangeOfficersLoyality("good_all", 5);
			DeleteAttribute(pchar, "questTemp.AdmiralMap");
			dialog.text = "Örülök, hogy elégedett. Sôt, mivel minden így alakult, van még egy ajánlatom az Ön számára.";
			link.l1 = "Mi lenne az? Nagyon figyelek.";
			link.l1.go = "best_map";
		break;
		
		case "best_map":
			dialog.text = "Miközben ezeket a térképeket rajzoltam neked, eszembe jutott egy gondolat, hogy bár egy felfedezônek jók, de nem nyújtanak mindent, amire egy tengeri kapitánynak szüksége van. Nézd meg magad: az összes öböl, föveny és lagúna nagyon pontosan ábrázolva van rajtuk, de nem tudod használni ôket a szigetek közötti útvonal kijelölésére.";
			link.l1 = "Ez igaz, a pályát nem lehet belôlük meghatározni. De semmiképpen sem merek panaszkodni, senor Dios! Ön úgy készítette el nekem a térképeket, ahogyan megegyeztünk, nem kevesebbet.";
			link.l1.go = "best_map_01";
		break;
		
		case "best_map_01":
			dialog.text = "De én is készíthetek neked szigetvilágtérképet! És nem olyat, amilyet a holland Nyugat-indiai Társaságtól lehet kapni, hanem egy egyedi, kiváló térképet.";
			link.l1 = "Köszönöm, senor Dios, de nekem nincs szükségem ilyen térképre. Azért köszönöm szépen az ajánlatot!";
			link.l1.go = "best_map_02";
			link.l2 = "Most viccelsz?! Senor Dios, hogyan utasíthatnám vissza? Csak mondja meg, mire van szüksége - nem sajnálom a pénzt vagy a szerszámokat!";
			link.l2.go = "best_map_04";
		break;
		
		case "best_map_02":
			dialog.text = "Nos, fel kellett ajánlanom. Mindenesetre öröm volt önnel üzletelni, senor "+pchar.lastname+"!";
			link.l1 = "Szintén! Sok szerencsét!";
			link.l1.go = "best_map_03";
		break;
		
		case "best_map_03":
			DeleteAttribute(pchar, "questTemp.AdmiralMapCopy");
			DialogExit();
			NextDiag.CurrentNode = "Dios";
		break;
		
		case "best_map_04":
			dialog.text = "A szerszámok már megvannak, köszönöm. Szükségem lesz egy egyszerű térképre az archipelágusról, valamint kérek egy iránytűt és egy hitelesített kronométert – a térképnek pontosnak kell lennie, különben ez csak szabotázs lenne. Fizetségül pedig – egy láda tele doblonnal.";
			if(CheckAMapItems())
			{
				link.l1 = "Minden, amit felsorolt, már nálam van. Tessék, itt van.";
				link.l1.go = "best_map_07";
			}
			link.l2 = "Egyszerű térkép az archipelágusról, iránytű, hitelesített kronométer, egy láda doblon. Megjegyeztem! A lehető leghamarabb hozom – várjon rám!";
			link.l2.go = "best_map_07e";
		break;
		
		case "best_map_07e":
			DialogExit();
			NextDiag.CurrentNode = "best_map_waititems";
		break;
		
		case "best_map_waititems":
			dialog.text = "Üdvözlöm, kedves barátom! Meghozta az egyszerű archipelágus-térképet, az iránytűt, a hitelesített kronométert és a doblonokkal teli ládát?";
			link.l1 = "Még nem, Señor Dios. De biztosan el fogom hozni!";
			link.l1.go = "best_map_07e";
			if(CheckAMapItems())
			{
				link.l2 = "Igen, Señor Dios. Itt van minden – tessék.";
				link.l2.go = "best_map_07";
			}
		break;
		
		case "best_map_07":
		    Log_Info("Átadtál egy szabályos szigetvilágtérképet, egy boussole-t, egy tarifás kronométert és egy ládát dublonnal.");
			TakeNItems(pchar,"chest", -1);
			TakeNItems(pchar,"map_normal", -1);
			TakeNItems(pchar,"bussol", -1);
			TakeNItems(pchar,"clock2", -1);
			dialog.text = "Nos, akkor nekilátok a munkának. Jöjjön vissza hozzám egy hét múlva, és ígérem, nem fogja megbánni!";
			link.l1 = "Nincs kétségem, Senor. Egy hét múlva találkozunk!";
			link.l1.go = "best_map_08";
		break;
		
		case "best_map_08":
			SetTimerFunction("AdmAtlas_comlete", 0, 0, 7);
			NextDiag.CurrentNode = "best_map_wait";
			pchar.questTemp.AdmiralAtlas = true;
			DialogExit();
		break;
		
		case "best_map_wait":
			if(CheckAttribute(pchar,"questTemp.AdmiralAtlas") && pchar.questTemp.AdmiralAtlas == "complete")
			{
				dialog.text = "Ah, da sind Sie ja, Señor "+pchar.lastname+"! Ich freue mich, Ihnen mitteilen zu können: Ich habe die Karte des Archipels fertiggestellt! Und ich versichere Ihnen, sie ist deutlich besser als die, die Sie mir überlassen haben.";
				link.l1 = "Mein Freund... Diese Karte ist atemberaubend! Das ist, wenn ich so sagen darf, ein wahres Meisterwerk! Wie kann ich Ihnen für alles danken, was Sie für mich getan haben?";
				link.l1.go = "best_map_09";
			}
			else
			{
				dialog.text = "Willkommen, Señor! Verzeihen Sie, aber die Karte ist noch nicht fertig.";
				link.l1 = "Ja, ich erinnere mich, Sie benötigen eine Woche. Ich wollte nur kurz nach Ihnen sehen.";
				link.l1.go = "best_map_wait_01";
			}
		break;
		
		case "best_map_wait_01":
			NextDiag.CurrentNode = "best_map_wait";
			DialogExit();
		break;
		
		case "best_map_09":
			dialog.text = "Ach, mein Freund, lassen Sie das. Es war mir eine Freude, eine solche Karte für einen ehrenwerten Kapitän anzufertigen, der sie wirklich zu schätzen weiß. Ach ja – hier ist übrigens Ihre einfache Karte zurück. Viel Glück auf See!";
			link.l1 = "Vielen, vielen Dank! Sie haben recht, diese Karte ist für mich einfach unbezahlbar. Auf Wiedersehen, Señor Dios!";
			link.l1.go = "best_map_10";
		break;
		
		case "best_map_10":
			TakeNItems(pchar,"Map_Best", 1);
			TakeNItems(pchar,"map_normal", 1);
			Log_Info("Kaptál egy kiváló szigetvilágtérképet!");
			PlaySound("interface\important_item.wav");
			NextDiag.CurrentNode = "Dios";
			DialogExit();
		break;
		
		case "LSC":
			dialog.text = "Tényleg?! Megtaláltad? Helyezze magát kényelembe, azt hiszem, a következô beszélgetés eltart egy darabig, igazam van?";
			link.l1 = "Tényleg sokat kell mesélnem a szigetrôl. De elôször is, szeretném, ha megígérnél nekem valamit. Látom, hogy becsületes ember vagy, így biztos vagyok benne, hogy megtartod a szavad...";
			link.l1.go = "LSC_1";
		break;
		
		case "LSC_1":
			dialog.text = "Mirôl beszél, kapitány?";
			link.l1 = "Ott emberek élnek... és nem fognak örülni, ha valaki beleavatkozik az életükbe. Nem hiszem, hogy egy esetlegesen érkezô valamilyen 'research' squadron érkezését örömmel fogadnák.";
			link.l1.go = "LSC_1_1";
		break;
		
		case "LSC_1_1":
			dialog.text = "";
			link.l1 = "Ezért azt szeretném, ha becsületszavát adná, hogy a beszélgetésünket követô tíz éven belül nem tesz közzé semmilyen olyan információt, amely felhasználható a sziget megtalálására. Nyugodtan közzétehetsz bármilyen információt a helyiekrôl, az életükrôl és így tovább, csak a sziget helyét ne fedd fel.";
			link.l1.go = "LSC_2";
		break;
		
		case "LSC_2":
			dialog.text = "Egyetértek, kapitány. Nemesi szavamat adom, hogy a következô tíz évben nem mondom el senkinek sem a Sziget helyét, sem semmilyen olyan információt, amely árthatna a lakosainak.";
			link.l1 = "Akkor hallgassa meg a történetemet. Írja le, ha akarja. Szóval, a Sziget egy csomó hajótöröttbôl áll, amelyeknek a héjai egy széles zátonyon hevernek...";
			link.l1.go = "LSC_3";
		break;
		
		case "LSC_3":
			DialogExit();
			SetLaunchFrameFormParam("Két órával késôbb...", "LSC_FinalDiosStory", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "LSC_4":
			dialog.text = "Hihetetlen! Nagyon értékes információkat mondott nekem, kapitány! de Betancourt admirális utódai a szigeten élnek! Most már tudjuk, mi történt a hajórajával. És a Karib-tengeri szigetvilág térképén most már egy üres foltal kevesebb van... Köszönjük szépen a történetet, "+pchar.name+"!";
			link.l1 = "Most már érted, miért kértelek, hogy nagyon óvatosan meséld újra az információimat?";
			link.l1.go = "LSC_5";
		break;
		
		case "LSC_5":
			dialog.text = "Értem. Biztos lehetsz benne, hogy megtartom a szavamat. Mondd csak... van valamilyen anyagi tulajdonságod a szigetrôl?";
			if (CheckCharacterItem(pchar, "LSC_navigation_map"))
			{
				link.l1 = "Van útvonalam az Elhagyott Hajók Szigetére. Tessék, nézd meg. Segítségükkel egy kis hajóval áthajózhatsz a zátonyokon és a törmelékeken, és biztonságosan partra szállhatsz a szigeten. Az útvonal nélkül lehetetlen elérni a szigetet.";
				link.l1.go = "LSC_6";
			}
			else
			{
				link.l1 = "Sajnos nekem nincsenek ilyenek.";
				link.l1.go = "LSC_7_1";
			}
		break;
		
		case "LSC_6":
			Log_Info("Vitorlás útbaigazítást adtál");
			PlaySound("interface\important_item.wav");
			dialog.text = "(néz) Egy ilyen kiváló dokumentum! Egy olyan ember rajzolta, aki ért a térképészethez. Még én sem tudnám jobban megcsinálni. Hihetetlen! Kapitány, miért nem adja meg nekem ezeket a vitorlás útvonalakat? A történet az történet, de ezt a papírt meg kell mutatni az Óvilág leghíresebb geográfusainak!";
			link.l1 = "Senor Dios, sajnos nekem magamnak kell ez a dokumentum. Mint már mondtam, nélküle lehetetlen áthaladni a szigetet körülvevô zátonyokon. De ha akarja, készíthet egy másolatot az útbaigazításról, és én csak örülni fogok, ha ön is birtokában lesz.";
			link.l1.go = "LSC_10";
			//link.l2 = "Senor Dios, unfortunately, I need this item for myself. As I have said, it is impossible to bypass the reefs around the Island without it. I'd sacrifice it in the name of science, but... I am sure that you understand.";
			//link.l2.go = "LSC_7";
		break;
		
		case "LSC_7":
			Log_Info("Vitorlás útbaigazítást kaptál");
			PlaySound("interface\important_item.wav");
			dialog.text = "Természetesen. Jogod van hozzá, bár kár érte... Mindenesetre köszönöm a történetet! Nagy szolgálatot tettél a földrajzosoknak, térképészeknek és más kíváncsi embereknek.";
			link.l1 = "Szívesen, senor. Nos, nekem most mennem kell. Viszontlátásra.";
			link.l1.go = "LSC_8";
		break;
		
		case "LSC_7_1":
			dialog.text = "Milyen kár... Mindenesetre köszönöm a történetét! Nagy szolgálatot tett a földrajzosoknak, térképészeknek és más kíváncsi embereknek.";
			link.l1 = "Szívesen, senor. Nos, nekem most mennem kell. Viszontlátásra.";
			link.l1.go = "LSC_8";
		break;
		
		case "LSC_8":
			dialog.text = "Persze, "+pchar.name+". Sok idôt szántál rám. Üdvözletemet küldöm Senor Svensonnak!";
			link.l1 = "Viszlát, Senor Dios.";
			link.l1.go = "LSC_9";
		break;
		
		case "LSC_9":
			DialogExit();
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 400);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 500); // харизма
			ChangeCharacterComplexReputation(pchar, "nobility", 5);// репутация-известность
			ChangeCharacterComplexReputation(pchar, "authority", 2);// репутация-авторитет
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, SPAIN, 5);
			DeleteAttribute(pchar, "questTemp.LSC.Dios");
			LAi_SetOwnerType(npchar);
		break;
		
		case "LSC_10":
			Log_Info("Vitorlás útbaigazítást kaptál");
			PlaySound("interface\important_item.wav");
			dialog.text = "Köszönöm szépen! Ez nagyon kedves öntôl. Adjon egy kis idôt...";
			link.l1 = "...";
			link.l1.go = "LSC_11";
		break;
		
		case "LSC_11":
			DialogExit();
			SetLaunchFrameFormParam("Két órával késôbb", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 0);
			npchar.dialog.currentnode = "LSC_12";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LSC_12":
			//RemoveItems(pchar, "LSC_navigation_map", 1);
			dialog.text = "Köszönöm szépen! Nagyon kedves volt öntôl. Most már nem csak szóbeli, hanem tárgyi bizonyítékunk is van... Nem hagyom jutalmazás nélkül, kapitány. Van egy kis ajándékom önnek.";
			link.l1 = "Miféle ajándékot?";
			link.l1.go = "LSC_13";
		break;
		
		case "LSC_13":
			sld = characterFromId("Pirates_shipyarder");
			sld.quest.sextant = "true"; // атрибут Алексу на хронометр
			GiveItem2Character(pchar, "sextant1"); 
			PlaySound("interface\important_item.wav");
			dialog.text = "Nemcsak a térképészet és a földrajz, hanem a matematika és a csillagászat is a szívem csücske. Egy évig tartott, amíg megpróbáltam létrehozni egy univerzális eszközt a szélességi és hosszúsági fokok mérésére. És némi elôrelépést értem el. Tessék, nézze meg:\nEz az én szextánsom. Magam terveztem. A probléma az, hogy nem mûködik. Rendkívül pontos kronométerre van szükség. Még azok is, amelyeket a legjobb mesteremberek készítettek, idôvel elfogadhatatlan hibákat adnak. Ezért az eszközöm egyelôre értéktelen.\nDe mivel sokat utazik, talán talál egy elég pontos kronométert ahhoz, hogy a szextáns mûködjön. Ha egyszer találsz egy ilyen órát - nem lesz szükséged Boussole-ra, iránytûre, asztrolábiumra, homokórára és egyéb gagyi kronométerekre - az én eszközöm mindet helyettesíteni fogja.";
			link.l1 = "Köszönöm, Senor Dios. Reméljük, hogy találok majd egy olyan kronométert, amely mûködôképessé teszi a találmányát. Szeretnék egy ilyen eszközt... mûködô állapotban. Nos, most mennem kell. Viszontlátásra.";
			link.l1.go = "LSC_8";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Te "+ GetSexPhrase("tolvaj vagy, látom! Ôrök, fogjátok el","tolvaj, látom! Ôrség, fogjátok el") +"!!!", "Nem hiszem el! Egy pillanatra elfordultam - és máris a holmimba merülsz! Állítsatok meg egy tolvajt!!!", "Ôrség! Rablás! Állítsanak meg egy tolvajt!!!");
			link.l1 = "Aaaah, ördög!!!";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}

bool CheckAMapItems()
{
	return GetCharacterItem(pchar,"chest")      && 
		   GetCharacterItem(pchar,"map_normal") &&
		   GetCharacterFreeItem(pchar,"bussol") &&
		   GetCharacterFreeItem(pchar,"clock2");
}