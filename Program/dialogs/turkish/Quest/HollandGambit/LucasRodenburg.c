// Лукас Роденбург - вице-директор ГВИК
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
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl"))
			{
				dialog.text = "Konuş bakalım, delikanlı, ama çabuk ol. Ben meşgul bir adamım.";
				link.l1 = " Kaptanlar aradığınızı duydum. ";
				link.l1.go = "Holl_start";	
			break;
			}
			dialog.text = "Benim için bir işiniz var mı?";
			link.l1 = "Hayır, üzgünüm. Gidiyorum.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Second_time":
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "BaltazarEsc")
			{
				dialog.text = "Şu ana kadar Sint Maarten yolunun yarısında olmalıydın, kaptan.";
				link.l1 = "Seyre çıkmaya hazırlanıyorum, efendim.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "BaltazarCom")
			{
				dialog.text = "Ah, kaptan, işte buradasınız! Gelişinizi fark etmemişim, az önce Ridderbrock'un mektubunu bitirdim. Üzerinizde büyük bir etki bırakmışsınız. Sizi 'tüccarların koruyucusu ve korsanların belası. Şirket'e Tanrı'nın armağanı!' diye anıyor. Buna ne dersiniz?";
				link.l1 = "Sıradan bir kaptan olarak kalmayı tercih ederim. Sıradan, ama zengin bir kaptan.";
				link.l1.go = "SantiagoTrip";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripBegin")
			{
				dialog.text = "Neden hâlâ buradasın ve Küba'ya doğru yolda değilsin?!";
				link.l1 = "Evet, evet, geliyorum, efendim.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripFinal")
			{
				sld = characterFromId("Santiago_usurer");
				dialog.text = "Ah, kaptan! Doğrusu endişelenmeye başlamıştım. Nasıl geçti?";
				link.l1 = "Kolay olmadı ama onu sonra anlatırım. Önce iş. Señor "+GetFullName(sld)+" Bana sana şunu söylememi söyledi: 'bu adam ölmeli.' O zaman Geraldi olayı kapanmış sayacak. Ayrıca, bu kararın ailelerinin iradesi olduğunu da söyledi.";
				link.l1.go = "SantiagoTrip_8";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripComplete")
			{
				dialog.text = "Seni görmek güzel, kaptan! Beni görmeye geldiğine sevindim.";
				link.l1 = "Günaydın, efendim. Sanırım yine Şirket için bir işiniz var?";
				link.l1.go = "JacobBerg";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "JacobTakeShip")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED)
				{
					dialog.text = "Sana gemini demirlemeni söyledim. Doğrudan verilen emirlere uymak için fazla mı aptalsın yoksa cahil misin?";
					link.l1 = "Hiçbiri değil, efendim. Yoluma devam ediyorum.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Demek gemini limana çektin. Şimdi sana kendi şebeğimi ödünç vereceğim. Bu göreve hemen başlamak için hazır mısın? Gemim donanımlı ve seyre çıkmaya hazır, endişelenecek hiçbir şeyin yok.";
					link.l1 = "Evet, elbette. Hazırım, Bay Rodenburg.";
					link.l1.go = "JacobBerg_6";
					DelLandQuestMark(npchar);
				}
			break;
			}
			if (pchar.questTemp.HWIC.Holl == "JacobLongway")
			{
				dialog.text = "Neden hâlâ buradasın? Hemen Longway'i gör.";
				link.l1 = "Üzgünüm, yoldayım.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MirageTake")//а вот теперь начинается дурдом с перебором кораблей
			{
				int iMir = 0;
				int iMef = 0;
				for(i = 0; i < COMPANION_MAX; i++)
				{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE) iMir = 1;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG) iMef = 1;
				}
				}//установили признак наличия кораблей в эскадре.
				RemoveItems(PChar, "JacobJournal", 1);//удалим журнал ван Берга
				pchar.quest.MirageConvoyOver.over = "yes"; //снять таймер
				if (iMir == 1 && iMef == 0)//потеряли Мейфенг
				{
					dialog.text = "Kapitein... Yolculuğunuzdan zaten haberdarım.";
					link.l1 = "Gerçekten mi? O halde şunu da biliyor olmalısın...";
					link.l1.go = "Jacob_lostMef";
					DelLandQuestMark(npchar);
					break;
				}
				if (iMir == 0 && iMef == 1)//потеряли Мираж
				{
					dialog.text = "Kapitein... Yolculuğunuzdan zaten haberdarım.";
					link.l1 = "Öyle mi? O zaman şunu da biliyor olmalısın...";
					link.l1.go = "Jacob_lostMir";
					DelLandQuestMark(npchar);
					break;
				}
				if (iMir == 0 && iMef == 0)//а это вообще плохо
				{
					dialog.text = "Kapitein... Yolculuğunuzdan zaten haberdarım.";
					link.l1 = "Öyle mi? O zaman şunu da biliyor olmalısın...";
					link.l1.go = "Jacob_failFull";
					DelLandQuestMark(npchar);
					break;
				}
					dialog.text = "İşte geldiniz, Kapitein... Yolculuğunuz hakkında zaten her şeyi biliyorum.";
					link.l1 = "Öyle mi? O zaman şunu da biliyor olmalısın...";
			link.l1.go = "Jacob_complete";
			DelLandQuestMark(npchar);
			break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Antigua'ya git. Hemen.";
				link.l1 = "Üzgünüm, yoldayım.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "FleetwoodSink" || pchar.questTemp.HWIC.Holl == "FleetwoodCapture")
			{//опять начинаем проверять корабли
				iMir = 0;
				for(i = 0; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE) iMir = 1;
					}
				}//установили признак наличия Миража в эскадре.
				pchar.quest.ToAntiguaOver.over = "yes"; //снять таймер
				if (iMir == 0)//потеряли Мираж
				{
					dialog.text = "Varışınızdan haberdar edildim, kaptan. Ayrıca Mirage'ımı savaşta kaybettiğinizi de biliyorum.";
					link.l1 = "İyi bilgilendirilmişsiniz, Bay Rodenburg. Tüm çabalarıma rağmen, onu kurtaramadık.";
					link.l1.go = "Fleetwood_fail";
					DelLandQuestMark(npchar);
				}
				else
				{
					dialog.text = "Gelişinizden haberdar edildim, kaptan. Mirage'ın güvenli bir şekilde limana yanaştığını görüyorum. Bu iyi.";
					link.l1 = "Her şey sizin talimatlarınızdı, efendim. Fleetwood'u öldürmemi emrettiniz ve o artık ölü. Mirage'ı limana geri getirmemi söylediniz, işte burada.";
					link.l1.go = "Fleetwood_complete";
					DelLandQuestMark(npchar);
				}
				pchar.quest.Meifeng_fail.over = "yes";
				Group_DeleteGroup("Meifeng_Empty");
				sld = characterFromId("MeifengCap");
				sld.lifeday = 0;//зачистим Мейфенг без китайца
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "Abby_prepare")
			{
				dialog.text = "Ah, işte buradasın. Seni görmek güzel. Söz verdiğim gibi, senin için bir görevim daha var.";
				link.l1 = "Dinliyorum, efendim.";
				link.l1.go = "Abby";
				DelLandQuestMark(npchar);
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.HWIC.Holl.LucasMoney") && pchar.questTemp.HWIC.Holl == "AbbyAgreeMarried")
			{
				dialog.text = "Ah, seni görmek ne güzel, oğlum. Geciktin, endişelenmeye başlamıştım. Abigail'den bir şey öğrenebildin mi?";
				link.l1 = "Sadece bununla kalmadım, diğer sorunlarını da çözdüm. Adayı ve Señor Shneur'un kayıp servetini buldum. Solomon mutlu, Abigail ise evlenme teklifine evet diyecek. Tebrikler, mynheer!";
				link.l1.go = "Abby_2";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "NotFindAbbyIsland")
			{
				dialog.text = "Ah, seni görmek ne güzel, dostum. Abigail'den bir şey öğrenebildin mi?";
				link.l1 = "Evet. Abigail ve babasıyla konuştum. Bir sorun var, efendim: babasının kaybolan serveti. Abigail kendini sana layık görmüyor, çeyizi olmayan bir kız olarak senin gibi bir beyefendiyle evlenirse insanların dedikodularından ve fısıltılarından korkuyor. Umarım bunu anlarsın.";
				link.l1.go = "Abby_6";
				DelLandQuestMark(npchar);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LucasMoney") && pchar.questTemp.HWIC.Holl == "AbbyAgreeMarried")
			{
				dialog.text = "Ah, dostum! Bana iyi haberler getirdiğine inanıyorum?";
				link.l1 = "Planın başarılı oldu. Abigail kabul edecek. Tebrikler, efendim.";
				link.l1.go = "Abby_8";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MerdokStart")
			{
				dialog.text = "Seni bekliyordum. Evlat, büyük bir tehlikedesin.";
				link.l1 = "Ne demek istiyorsun?";
				link.l1.go = "Merdok";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MerdokDie")
			{
				dialog.text = "Limanımdaki adamlarım bana geldiğini söyledi. Johan van Merden öldü mü?";
				link.l1 = "Evet. O ve suç ortağı gitti. Zorlu bir dövüştü, ama sonuna kadar dayandım.";
				link.l1.go = "Merdok_4";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Konuşacak başka bir şeyimiz yok, kaptan.";
			link.l1 = "Anladım, gidiyorum.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "Ne oldu? Zaman nakittir.";
		link.l1 = "Üzgünüm, gidiyorum.";
		link.l1.go = "exit";
		break;
		
//------------------------------------------------1 задание--------------------------------------------
		case "Holl_start":
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Bridgetown_tavernkeeper"));
			DelLandQuestMark(characterFromId("Knippel"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Belki. Sen kimsin? Çabuk konuş, zaman para.";
			link.l1 = "Ben kaptanım "+pchar.name+", gemim ve  size yardımcı olabilir.";
			link.l1.go = "Holl_start_0";			
		break;
		
		case "Holl_start_0":
			dialog.text = "Hm, potada denenmesi gereken bilinmeyen bir alaşım.";
			link.l1 = "Bu yüzden buradayım, efendim.";
			link.l1.go = "Holl_start_1";			
		break;
		
		case "Holl_start_1":
			pchar.questTemp.HWIC.Holl.PirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Pekâlâ, cesaretinin rengini göreceğiz. Peki, adı her neyse Kaptan, Balthazar Ridderbrock'u tanıyor musun? Hayır mı? Ne şanslısın. Onun gibi açgözlü, huysuz, çabuk öfkelenen ahmaklara pek rastlanmaz.\nAma anlaşılan bu dikkat çekici özellikler bile ona yetmemiş, öyle ki, Longway adında bir filibustere hakaret edecek kadar akıllıymış."+GetName(NAMETYPE_ORIG,pchar.questTemp.HWIC.Holl.PirateName,NAME_NOM)+" yerel meyhanede ve hakarete uğrayan kişi kılıcına dokunduğu anda muhafızları çağırmış...";
			link.l1 = "...ve korsanı buldukları ilk boş iple astılar mı?";
			link.l1.go = "Holl_start_2";			
		break;
		
		case "Holl_start_2":
			dialog.text = "O kadar basit değil. "+GetName(NAMETYPE_ORIG,pchar.questTemp.HWIC.Holl.PirateName,NAME_NOM)+" sıradan bir korsan değil, Hollandalı bir kapitan, İngilizlerle yapılan son iki savaşın gazisi. Buradaki vergi mükellefleri ona oldukça sıcak bakıyor. Ridderbrock için aynısını söyleyemem.";
			link.l1 = "Demek korsanımız hâlâ hayatta?";
			link.l1.go = "Holl_start_3";			
		break;
		
		case "Holl_start_3":
			dialog.text = "Evet, ama gerçekten çok öfkeli. Bu yüzden Ridderbrock ödü patlamış halde korkuyor.";
			link.l1 = "Sanırım şansım yakında tükenmek üzere. Mynheer Ridderbrock ile ne zaman görüşeceğim?";
			link.l1.go = "Holl_start_4";			
		break;
		
		case "Holl_start_4":
			dialog.text = "Çok yakında. Philipsburg'un iyi insanları bir şeker sevkiyatını bekliyor, ki bunu ortak tanıdığımız Ridderbrock teslim etmeye söz verdi. Adamı çizmelerinin derisine bile layık görmem ama ne yazık ki bizim için çalışıyor, o yüzden hemen liman ofisine git. Ridderbrock'u orada bul ve ona hemen yelken açmasını emrettiğimi söyle.\nOnu gizlice takip edeceksin ve... Philipsburg'a sağ salim ulaşmasını sağlayacaksın. İstemiyorum ki "+GetName(NAMETYPE_ORIG,pchar.questTemp.HWIC.Holl.PirateName,NAME_NOM)+" Şirketin itibarını yüküyle birlikte Karayipler'in dibine göndermek için. ";
			link.l1 = "Off, bir koruma görevi. Peki ya bu... tatsız işin ödemesi ne olacak?";
			link.l1.go = "Holl_start_5";			
		break;
		
		case "Holl_start_5":
			dialog.text = "Kapitein, önce işi hallet. Balthazar, varış noktasına ulaştığında sana ödemesini yapacak. Philipsburg'da! Davy Jones'un sandığında değil! İş bitince bana tekrar rapor ver. Başarılı olursan, hem benim hem de Şirket'in desteğine güvenebilirsin. Gidebilirsin.";
			link.l1 = "Görüşürüz, mynheer.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Create_Baltazar");
			pchar.questTemp.HWIC.Holl = "BaltazarEsc";
			NextDiag.TempNode = "Second_time";
			pchar.quest.HWIC_ReturnOfficer.over = "yes";//чтобы офицер не доставал
			pchar.questTemp.HWIC.CanTake.Holl = "true";//признак, что голландка уже бралась
		break;
		
//----------------------------------------------задание 1а--------------------------------------------	
		case "SantiagoTrip":
			dialog.text = "Evet, Ridderbrock bir Hollandalı için bile pinti bir piçtir. Neyse, artık beni ilgilendirmiyor. Şimdi senin hakkında konuşalım, Kaptan Her Neyse Adın Ne. Tarzını beğendim, bu yüzden sana başka bir iş teklif edeceğim. Bu sefer ücretini ben ödeyeceğim.";
			link.l1 = "Sizi dinliyorum, efendim.";
			link.l1.go = "SantiagoTrip_1";			
			AddSimpleRumourCity("Ah, so you are the brave kapitein who escorted that scoundrel Ridderbrock? We heard all about about it... He paid you only five thousand pesos! He's been boasting about it nonstop at the tavern in Philipsburg drunk as a swine. If I were you captain, I drag him out into the street and thrash him.", "Villemstad", 20, 3, "");//слух по 1 заданию
		break;
		
		case "SantiagoTrip_1":
			dialog.text = "Çok önemli bir mesele için güvenilir bir adama ihtiyacım var. Ridderbrock meselesinde iyi iş çıkardın, bu yüzden Şirket bunu sana emanet edebileceğime inanıyor.";
			link.l1 = "Sanırım onurlandırıldım. Sorun nedir?";
			link.l1.go = "SantiagoTrip_2";
		break;
		
		case "SantiagoTrip_2":
			sld = characterFromId("Santiago_usurer");
			dialog.text = "Sana tam ayrıntı veremem, ama bil ki bu benim işim değil, Şirket’in işi; yani bizim gözümüzde iyi bir izlenim bırakma şansın var ve emin ol, bu oldukça kârlı olabilir.\nKüba’daki Santiago’ya git ve bu paketi Don’a teslim et "+GetFullName(sld)+". Geraldi'nin bankasında yüksek bir mevkii var ve ayrıca benim... bizim iş ortağımız. Şimdi sana vereceğim bu altını ona teslim edeceksin. Dürüstlüğüne güveniyorum, kaptan. Ya da dürüstlüğüne değilse, hayatta kalma içgüdüne. Şirket, bizden çalmaya kalkanları her zaman bulur.";
			link.l1 = "Bana inanmıyor musunuz, mynheer?";
			link.l1.go = "SantiagoTrip_3";
		break;
		
		case "SantiagoTrip_3":
			if (pchar.BaseNation == ENGLAND || pchar.BaseNation == FRANCE) sTemp = " I am also giving you this short-term Company trade license in order to spare you from any diplomatic entanglements with the Spanish. This will allow you to dock at Spanish colonies for some time.";
			else sTemp = "";
			dialog.text = "Şu anda sana güvenmemek için bir sebebim yok. İnan bana, şüphelensem bu konuyu seninle konuşmazdım bile. Bil ki bu işi ayarlamak için çok zaman harcadık, bu yüzden teslimat için sadece on beş günün var."+sTemp+"\nMesajım ve paketim zamanında teslim edilmeli. Bu çok önemli, oğlum. Acele et, ama dikkatli ol, bu iş kolay olmayacak.";
			link.l1 = "Başka bir şey var mı? Neden beni uyarıyorsunuz, Bay Rodenburg?";
			link.l1.go = "SantiagoTrip_4";
		break;
		
		case "SantiagoTrip_4":
			if (pchar.BaseNation == ENGLAND || pchar.BaseNation == FRANCE) GiveNationLicence(HOLLAND, 20);
			dialog.text = "Şöyle diyelim, bazı şüphelerim var. Merak etme, eğer işi geçen seferki kadar hızlı halledersen, Şirket’in hassas meselelerinde değerli bir ajan olma şansın olacak.";
			link.l1 = "Tek yapmam gereken bu mektubu ve parayı on beş gün içinde Santiago’daki bankacıya teslim etmek mi? Yüzeyde pek zor görünmüyor.";
			link.l1.go = "SantiagoTrip_5";
		break;
		
		case "SantiagoTrip_5":
			dialog.text = " O kadar acele etme, delikanlı... Sanırım bu işin ciddiyetini tam olarak kavrayamadın. Bu işi başarırsan sana gerçekten minnettar kalırım. Ama başarısız olursan, fena halde sinirlenirim. O durumda, seni rezil ederim. Anlaştık mı, kapitein "+GetFullName(pchar)+"?";
			link.l1 = "Anladım. Söz veriyorum. Keyfini yerinde tutmak için elimden geleni yapacağım.";
			link.l1.go = "SantiagoTrip_6";
		break;
		
		case "SantiagoTrip_6":
			dialog.text = "Pekâlâ. Şimdi mektubu ve şu sandıkları al, şartları unutma. Bir de, Santiago’da başını belaya sokma.";
			link.l1 = "Pekâlâ.";
			link.l1.go = "SantiagoTrip_7";
		break;
		
		case "SantiagoTrip_7":
			DialogExit();
			GiveItem2Character(pchar, "NPC_Letter");
			ChangeItemDescribe("NPC_Letter", "itmdescr_NPC_Letter4");
			TakeNItems(pchar, "chest", 5); 
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("SantiagoTripOver", 0, 0, 32, false);
			}
			else SetFunctionTimerCondition("SantiagoTripOver", 0, 0, 16, false); //таймер
			AddQuestRecord("Holl_Gambit", "1-43");
			pchar.questTemp.HWIC.Holl = "SantiagoTripBegin";
			AddMapQuestMarkCity("Santiago", true);
			AddLandQuestMark(characterFromId("Santiago_usurer"), "questmarkmain");
		break;
		
		case "SantiagoTrip_8":
			dialog.text = "'Ölmeli'... öylece. Bunu beklemiyordum. Hm. İşini iyi yapmışsın, kaptan. Şimdi bana bir rapor ver.";
			link.l1 = "Özel bir şey yoktu... çocuk oyuncağıydı.";
			link.l1.go = "SantiagoTrip_9";
			link.l2 = "Santiago'da bir adam tarafından sersemletilip kaçırıldım. Senin Geraldi ile olan işine fazlasıyla ilgi gösteriyordu. Kaçmayı başardım ama önce onu öldürmek zorunda kaldım. Geriye bıraktığı tek ipucu, Gaston adında bir adamın ismiydi. Bütün bunların neyle ilgili olduğuna dair hiçbir fikrim yok.";
			link.l2.go = "SantiagoTrip_10";
			link.l3 = "Santiago'da bir adam tarafından sersemletilip kaçırıldım. Geraldi ile olan işinle çok ilgileniyordu. Kaçmayı başardım ama önce onu öldürmek zorunda kaldım. Onu cehenneme göndermeden önce ağzından tek laf alamadım.";
			link.l3.go = "SantiagoTrip_11";
		break;
		
		case "SantiagoTrip_9":
			dialog.text = "Şirketin minnettarlığı sadece sözlerle sınırlı değil. Al ödülünü, bunu hak ettin.";
			link.l1 = "Şirket için çalışmak oldukça kârlı.";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_10":
			dialog.text = "Ne! Kaçırılma... Bir dakika, dur... Gaston! Anlıyorum... Sanırım öyle. Ah, evlat, seni bayağı bir işe bulaştırmışlar. Bilinmez sulardayız, bakalım neler olacak. Sağ salim kurtulmana sevindim.\nŞimdi daha hoş şeylerden bahsedelim – bu ödülü kabul et, fazlasıyla hak ettin.";
			link.l1 = "Şirket için çalışmak oldukça kârlı";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_11":
			dialog.text = "Saçmalık! Seni kaçırmak... Yine de bazı şüphelerim var. Benim için çalışmaya devam edersen daha fazlasını öğrenirsin. Şanslısın ve başardığına sevindim.\nŞimdi daha hoş şeylerden konuşalım – bu ödülü kabul et, fazlasıyla hak ettin.";
			link.l1 = "Şirket için çalışmak oldukça kârlı";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_12":
			AddMoneyToCharacter(pchar, 25000);
			dialog.text = "Aynen öyle, evlat! Eğer birlikte çalışmaya devam edersek, Şirket’in iyi maaşlı bir ajanı olabilirsin. Şimdi git, yolculuğunun yorgunluğunu at. Beklentilerimi fazlasıyla karşıladın. Bir hafta sonra tekrar gelirsen çok memnun olurum, yapacak daha çok işimiz var.";
			link.l1 = "Bana güvenebilirsiniz, Bay Rodenburg.";
			link.l1.go = "SantiagoTrip_13";
		break;
		
		case "SantiagoTrip_13":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "true";
			AddQuestRecord("Holl_Gambit", "1-46");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 80);
			AddSimpleRumourCity("My brother at the Company says that Mynheer Rodenburg is quite pleased by your performance, kapitein. Don't lose your chance, Lucas rarely shows such favor.", "Villemstad", 10, 3, "");
			SetTimerFunction("GollandGambit_2_ZadanieStart", 0, 0, 7);
		break;
		
//-----------------------------------------------2 задание--------------------------------------------
		case "JacobBerg":
			dialog.text = "Zekisin kaptan. Aynen öyle. Şimdi yaklaşan görevin ayrıntılarını konuşalım...";
			link.l1 = "Tamamen dinliyorum.";
			link.l1.go = "JacobBerg_1";			
		break;
		
		case "JacobBerg_1":
			dialog.text = "Sana çok ciddi ve önemli bir görevim var ve her şeyi talimatlarıma uygun şekilde yapmanı bekliyorum. Bildiğin gibi, Birleşik Eyaletler ile İngiltere arasındaki ilişki... pek dostane sayılmaz. İngilizler, dünyayı yalnızca kendilerinin yönetmesi gerektiğine inanıyor. Sorun şu ki, herkes bu iddiaya katılmıyor. Onlar ticaret yapmak için nereye yelken açarsa açsın, emin ol Hollanda Batı Hindistan Şirketi oraya ilk giden olmuştur. Biz Hollandalıların dünyadaki en büyük ticaret filosu var ve askeri filolarımız Cumhuriyet’in çıkarlarını hem burada hem de yurtdışında koruyabilir. İngilizler ticari gücümüzü kıskanıyor ve Şirket’in faaliyetlerini sabote etmek için ellerinden geleni yapıyorlar. Şimdi, Richard Fleetwood adında bir İngiliz donanma kaptanı var. Ortaklar Topluluğu’nun resmi subayı olmasına rağmen, şu anda korsanlık yapıyor. Karayipler’de Hollanda bayrağı altında yelken açmaya cüret eden her gemiye saldırıp yağmalıyor. Yaptıklarını, İngiliz tüccarlarını batıran ‘hayalet gemi’ye karşı alınan önlemler olarak açıklıyor. Bu ‘hayalet gemi’nin Hollanda hükümetinden alınmış bir korsanlık mektubuyla hareket eden bir kaper olduğunu iddia ediyor. ‘Hayalet gemi’yi duydun mu, kaptan?";
			link.l1 = "Böyle saçmalıkları her meyhanede duyabilirsin. Yaşlı bir lostromoya biraz rom ısmarla, istediğin hikâyeyi dinlersin...";
			link.l1.go = "JacobBerg_2";
		break;
		
		case "JacobBerg_2":
			dialog.text = "Bu mesele bir ayyaşın hayali değil. Bu 'hayalet gemi'nin faaliyetlerini araştırdım. Onun aslında sıradan adamların çalıştırdığı, ahşap ve yelkenli bir tekne olduğunu öğrendim, adı 'Mirage' olan bir ketch. Geminin kaptanı Jacob van Berg adında biri ve bu gemiyi efsanevi 'Uçan Hollandalı' gibi gösteriyor.";
			link.l1 = "Van Berg mi? Bu Hollandalı bir soyadı. Gerçek bir 'Uçan Hollandalı', öyle mi?";
			link.l1.go = "JacobBerg_3";
		break;
		
		case "JacobBerg_3":
			dialog.text = "Doğru. Jacob van Berg bir Hollandalı, aslen Leidenli. Ama Cumhuriyet onu çoktan darağacına mahkûm etti. O kaçak bir suçlu, sadece kendi çıkarları için hareket eden bir korsan. Richard Fleetwood, van Berg’in peşinde. Bu gerçeği o küstah İngiliz’e karşı kullanacağız.\nFleetwood’u hemen öldürmek istemem, gerçi bunu çoktan hak etti. Onun için ölüm yeterli olmaz. Onu sadece öldürmek değil, adını ve onurunu da yok etmek istiyorum. Asıl istediğim bu. Bu diğer kibirli İngiliz domuzlarına da ders olur.\nŞimdi ayrıntılara geçelim.";
			link.l1 = "Mynheer, bu artık kişisel bir meseleye benzemeye başladı...";
			link.l1.go = "JacobBerg_4";
		break;
		
		case "JacobBerg_4":
			dialog.text = "Bu seni ilgilendirmez. Emirleri yerine getir, sonra paranı alırsın. Adamım sayesinde Jacob van Berg’in 'Mirage'ıyla nerede saklandığını öğrendim. Güney İspanyol Ana Karası’ndaki bir şehirden çalışıyor. Ona git ve hayalet gemisini nereye demirlediğini öğren.\nSonra onu öldür, 'Mirage'ı bul, ganimet olarak al ve buraya getir. 'Mirage'ı mutlaka ele geçirmelisin, sakın batırmayı aklından bile geçirme.";
			link.l1 = "Oldukça basit görünüyor. Van Berg’i nerede aramalıyım?";
			link.l1.go = "JacobBerg_5";
		break;
		
		case "JacobBerg_5":
			dialog.text = "Tüm ayrıntıları sana adamım verecek. Adı Longway, Çinli bir adam. Bu görev için sana kendi gemimi, 'Meifeng' adlı xebec'i tahsis ediyorum. Longway onun kaptanı, ama bu sefer senin emirlerini dinleyecek.\nTüm gemilerini liman ofisine götürüp oraya demirle. İşin bitince bana dön.";
			link.l1 = "Pekala, liman müdürünü ziyaret edeceğim. Seni fazla bekletmeyeceğim.";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Holl = "JacobTakeShip";
			AddLandQuestMark(characterFromId("Villemstad_portman"), "questmarkmain");
		break;
		
		case "JacobBerg_6":
			dialog.text = "Longway seni dışarıda bekliyor. Yeni gemini gösterecek ve van Berg'in nerede olduğuna dair bazı bilgiler verecek. İyi şanslar, kaptan, beni hayal kırıklığına uğratma. 'Meifeng'i bana geri getirmek zorunda olduğunu unutma, bu yüzden 'Mirage'ı alırken onu batırmamaya çalış.";
			link.l1 = "Geliyorum!";
			link.l1.go = "JacobBerg_7";	
		break;
		
		case "JacobBerg_7":
			DialogExit();
			pchar.quest.Create_Longway.win_condition.l1 = "location";
			pchar.quest.Create_Longway.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Create_Longway.function = "Create_Longway";
			pchar.questTemp.HWIC.Holl = "JacobLongway";
			AddQuestRecord("Holl_Gambit", "1-7");
			pchar.questTemp.HWIC.TakeQuestShip = "true";//все ПУ недоступны для стоянки до поры, также корабль нельзя продать
			pchar.questTemp.HWIC.HollEquip = "true";//форма солдат
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
		break;
		
		//дурдом продолжается
		case "Jacob_lostMir":
			dialog.text = "Seni beceriksiz ahmak. Korsan gemisini ele geçirme görevinde başarısız oldun. Bütün planlarım mahvoldu. 'Meifeng'i senden alıyorum. Defol, artık sana ihtiyacımız yok.";
			link.l1 = "Üzgünüm. Elveda, Bay Rodenburg.";
			link.l1.go = "Jacob_RemoveShip";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MAYFANG;
		break;
		
		case "Jacob_lostMef":
			dialog.text = "Sen tam bir ahmaksın. 'Meifeng'i kaybettin. Bu kabul edilemez... 'Mirage'ı senden alacağım ve kaybımın karşılığı olarak ödemen de kesilecek. Defol git, artık sana ihtiyacımız yok.";
			link.l1 = "Üzgünüm. Elveda, Bay Rodenburg.";
			link.l1.go = "Jacob_RemoveShip";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MIRAGE;
		break;
		
		case "Jacob_failFull":
			dialog.text = "Tanrım, gerçekten de ender rastlanan bir örneksin. Hem beceriksiz bir serseri hem de tam bir aptalsın. Mirage'ı ele geçiremedin ve üstüne Meifeng'i de kaybettin. Defol git ofisimden!";
			link.l1 = "Gidiyorum.";
			link.l1.go = "exit";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Longway");
			AddDialogExitQuestFunction("LandEnc_OfficerFired");//Лонгвэя из офицеров
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Detector = "holl_fail";
		break;
		
		case "Jacob_complete":
			dialog.text = "Well done. Word of your success has already reached my ears. Van Berg is dead and you have captured his ship. Your payment is 50,000 pesos, take it.\nI am retrieving the 'Meifeng' from you. Now it is time for you to take command of the 'Mirage'; she will play an important role in the next stage. Are you ready?";
			link.l1 = "Evet, Bay Rodenburg.";
			link.l1.go = "Fleetwood";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MAYFANG;
			AddDialogExitQuestFunction("Jacob_RemoveShip");	
			AddSimpleRumourCity("They say that you are on special assignment for Mynheer Rodenburg himself. Something about sending those English to the bottom of the sea. It seems that you are a man on the rise, kapitein.", "Villemstad", 15, 3, "");
		break;
		
		case "Jacob_RemoveShip":
			DialogExit();
			AddDialogExitQuestFunction("Jacob_RemoveShip");	
			sld = characterFromId("Longway");
			sld.lifeday = 0;
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Detector = "holl_fail";
			AddSimpleRumourCity("They say that you have failed Mynheer Rodenburg himself. Good luck, you'll need it.", "Villemstad", 20, 3, "");
		break;
		
//----------------------------------------------3 задание-------------------------------------------------
		
		case "Fleetwood":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = "Now we deal with Fleetwood. You are going to lure him out using the 'ghost ship' Mirage that he has been hunting so enthusiastically. Set a trap near Dominica; the Mirage will serve as bait.\nFirst, you will let Fleetwood know that the Mirage was seen not far from Dominica. Our brave Englishman will drop everything he's doing and rush straight to Dominica in search of his prey. Don't speak to Fleetwood directly or you won't survive the encounter. Find the drugstore in St. John's. The apothecary, John Murdock, is an old friend of mine.\nTell him that you are acting under my command and he will help you find some local ears to fill with juicy lies about the 'ghost ship' attacking English merchants near Dominica.";
			link.l1 = "Bunu yapabilirim. Hedef Dominika'da Fleetwood'a pusu kurmak, doğru mu?";
			link.l1.go = "Fleetwood_1";
		break;
		
		case "Fleetwood_1":
			dialog.text = "Aynen öyle. Longway ve 'Meifeng' seni Dominika yakınlarında bekleyecek. İkiniz birlikte o İngiliz köpeğini kolayca alt edebilirsiniz. Gemisine çıkıp kamarasını arayın. Günlüğünü istiyorum. Bunun için fazladan ödeyeceğim.\nAma asıl önceliğin o alçak Fleetwood'u öldürmek, bu yüzden gemisine çıkmak mümkün olmazsa - onu denizin dibine gönder. Her şeyden önemlisi, 'Mirage'ı ne pahasına olursa olsun korumalısın. O, planın bir sonraki aşamasında kritik bir rol oynayacak.";
			link.l1 = "Anlaşıldı.";
			link.l1.go = "Fleetwood_2";
		break;
		
		case "Fleetwood_2":
			dialog.text = "Sana bir tavsiye, kaptan. St. John's limanına demir atma. Adanın koylarından birine çık ve şehre ormandan yürüyerek git, yoksa John seninle konuşmaz. Eğer fazla dikkat çekersen, seni tanımıyormuş gibi yapar. Ayrıca denizde dikkatli ol - 'Mirage' İngiliz kolonileri arasında kötü şöhretli, bu yüzden onların savaş gemilerinden ve yerleşimlerinden uzak dur, yoksa bir grup deniz kurdunun saldırısına uğrayabilirsin. Hepsi bu. Tanrı yardımcın olsun.";
			link.l1 = "Aye aye.";
			link.l1.go = "Fleetwood_3";
		break;
		
		case "Fleetwood_3":
			DialogExit();	
			pchar.questTemp.HWIC.Holl = "toAntigua";
			AddQuestRecord("Holl_Gambit", "1-15");
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			SetFunctionTimerCondition("ToAntiguaOver", 0, 0, 60, false); //таймер 2 месяца
			AddMapQuestMarkShore("Shore1", false);
			AddMapQuestMarkShore("Shore2", false);
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Fleetwood_complete":
			if (pchar.questTemp.HWIC.Holl == "FleetwoodSink")//Флитвуд утоп с журналом
			{
				dialog.text = "Geri döndünüz, kaptan... Richard Fleetwood'un seyir defteri yanınızda mı?";
				link.l1 = "Maalesef, hayır. Gemisine çıkma fırsatım olmadı, çünkü o batırmadan önce yetişemedim.";
				link.l1.go = "Fleetwood_complete_1";
				break;
			}
			if (!CheckCharacterItem(pchar, "FleetwoodJournal"))
			{
				dialog.text = "Geri döndünüz, kaptan... Richard Fleetwood'un seyir defteri yanınızda mı?";
				link.l1 = "Maalesef bulamadım. Valkyrie'ye çıkıp adamı göğüs göğüse dövüşte öldürdüm, ama günlüğünü bulamadım. Adamlarından biri cephaneliği ateşe verdi ve canımızı kurtarmak için sadece birkaç saniyemiz vardı.";
				link.l1.go = "Fleetwood_complete_1";
				break;
			}
			dialog.text = "Geri döndünüz, kaptan... Richard Fleetwood'un seyir defteri yanınızda mı?";
			link.l1 = "Yaptım. İşte burada. Valkyrie'ye binmeyi başardım, ama neredeyse elimizden kaçıyordu. O alçak, gemisindeki cephaneyi ateşe verip havaya uçurdu. Canımızı zor kurtardık.";
			link.l1.go = "Fleetwood_complete_2";
		break;
		
		case "Fleetwood_complete_1":
			AddMoneyToCharacter(pchar, 100000);
			dialog.text = "Bu gerçekten büyük bir talihsizlik, elimizdeki birçok soruya cevap olabilirdi. Ama artık önemi yok. O küstah İngiliz köpeğini öldürdün, en önemlisi de bu. İşte ödülün - 100.000 peso. 'Mirage'ı senden alıyorum, bu gemiyi İngiltere'ye geri götüreceğiz.";
			link.l1 = "Ne oluyor böyle?! Güzel bir gemiydi, onu kendime saklamak istemiştim!";
			link.l1.go = "Fleetwood_complete_3";
		break;
		
		case "Fleetwood_complete_2":
			AddMoneyToCharacter(pchar, 150000);
			RemoveItems(PChar, "FleetwoodJournal", 1);
			dialog.text = "Excellent! You are a very capable man. If all our captains were like you, the Dutch Republic would be first among the greatest maritime nations in history. Here is your reward - 100,000 pesos, and 50,000 pesos extra for the logbook. I am taking the 'Mirage' from you; we are going to return this ship to England.";
			link.l1 = "Ne oluyor böyle?! O gemi harika, onu kendime saklamak istemiştim!";
			link.l1.go = "Fleetwood_complete_3";
		break;
		
		case "Fleetwood_complete_3":
			dialog.text = "Oğlum, sen mükemmel bir askersin, ama bana ve siyaset konusundaki tecrübeme güven. Fleetwood hakkında söylediklerimi hatırla. Onun adını ve itibarını bir değirmen taşına çivileyip derinliklere fırlatacağım. Ve Port Royal'deki o kibirli soylular bunu yutmak ve boğulmak zorunda kalacaklar. Richard Fleetwood'u, 'hayalet gemi' Mirage'ın kaptanı, İngiltere ve Hollanda'yı birbirine düşüren, iki ulusun da masum vatandaşlarını yağmalayan, talan eden ve öldüren bir kurtadam yapacağız; sırf kendini zengin etmek için! Ne rezalet! Kanıtlarım ve tanıklarım hazır bile, ama 'Mirage' bu kusursuz oyunumun başrolü olacak.";
			link.l1 = "Vay canına, demek öyle! Kendi planın için benim mükemmel gemimi feda edeceksin!?";
			link.l1.go = "Fleetwood_complete_4";
			AddDialogExitQuestFunction("Lucas_ExangeShip");
		break;
		
		case "Fleetwood_complete_4":
			dialog.text = "Diline dikkat et, delikanlı, bu bir savaş. Bazen siyasi hedeflerimize ulaşmak için sadece insanları değil, gemileri ve zengin yerleşimleri de feda etmemiz gerekir. Her savaşın kayıpları olur... Kayıplardan söz etmişken, sana kötü bir haberim var.\nSen yokken, Willemstad İngiliz korsanları tarafından saldırıya uğradı. Kale onları püskürtmeyi başardı, ama onlar ateş gemileriyle limana girmeden önce değil.\nGeminin demirdeyken yakalandı ve su hattına kadar yandı. Tamamen kaybettin.";
			link.l1 = "Mynheer, şu anda benimle dalga geçiyor olmalısınız. Kahretsin her şeyi! Şimdi ne yapmam gerekiyor?!";
			link.l1.go = "Fleetwood_complete_5";			
		break;
		
		case "Fleetwood_complete_5":
			dialog.text = "Don't be so upset, kapitein, I also have good news. To salve your indignation, I am giving you my Beautiful Wind, the xebec 'Meifeng'. You are free to use the ship in any way you wish, within reason. Additionally, meet me tomorrow at the governor's residence; you have been nominated for a state award with the gratitude of the Dutch Republic and the West India Company. Don't leave town until you receive it, kapitein.";
			link.l1 = "Bu, kayıplarımın acısını biraz hafifletiyor. Onur duydum. Bu arada, efendim, Longway nereye gitti?";
			link.l1.go = "Fleetwood_complete_6";
		break;
		
		case "Fleetwood_complete_6":
			dialog.text = "Longway'e Dominika'ya gitmesini emrettikten hemen sonra aniden ortadan kayboldu. İngiliz ajanlarının ona saldırmış olmasından şüpheleniyorum... ya da belki de değil. Araştırıyorum.";
			link.l1 = "Anladım. Dominika'da onun yardımı çok makbule geçerdi. Fleetwood ve 'Valkyrie’si korkutucu bir ikiliydi. Umarım Longway hâlâ hayattadır... Tot ziens, mynheer!";
			link.l1.go = "Fleetwood_complete_7";
			pchar.questTemp.HWIC.Holl = "Award";
			AddQuestRecord("Holl_Gambit", "1-24");
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", true);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", true);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", true);
		break;
		
		case "Fleetwood_complete_7":
			DialogExit();
			AddDialogExitQuestFunction("GollandGambit_AwardFromLucas_1");
			AddSimpleRumour("Tell me captain, was that damned English dog Fleetwood was really responsible for plundering English 'and' Dutch merchants? Really? Such an artful dodger! It is good that you have eliminated this bastard. You are a real hero, captain!", HOLLAND, 10, 3);
		break;
		
		case "Fleetwood_fail":
			dialog.text = "Sen sadece sıradan bir soytarı değilsin, bütün sirksin. Son perdeye bu kadar yaklaşmıştık ve sen her şeyi berbat ettin... Fleetwood'u ortadan kaldırman için sana 30.000 peso ödeyeceğim. Sana verecek başka görevim kalmadı ve anlaşmamız burada bitiyor. Defol.";
			link.l1 = "Nasıl istersen.";
			link.l1.go = "Fleetwood_fail_1";			
		break;
		
		case "Fleetwood_fail_1":
			AddMoneyToCharacter(pchar, 30000);
			dialog.text = "Sana kötü bir haberim var.\nSen yokken, Willemstad İngiliz korsanlarının saldırısına uğradı. Kale onları püskürtmeyi başardı, ama yangın gemileriyle limana girmeden önce değil.\nGeminin demirliyken yakalandı ve su hattına kadar yandı. Tamamen kaybettik.";
			link.l1 = "Sanırım gidip kendi başımın çaresine bakacağım o zaman! Hiçbir şey için teşekkürler!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Holl = "end";
			pchar.questTemp.HWIC.Detector = "holl_fail";
			AddSimpleRumour("Tell me, captain, is it true that you have sunk this damned English dog Fleetwood? Really? It is good that you have eliminated this bastard. You did well, captain!", HOLLAND, 15, 3);
		break;
		
		case "LucasAward":
			dialog.text = "Kapitein "+GetFullName(pchar)+"Richard Fleetwood gibi tehlikeli bir devlet suçlusunu ortadan kaldırdığınız, Cumhuriyet'e karşı düzenlenen hain İngiliz komplosunu açığa çıkardığınız ve gösterdiğiniz cesaret ile yiğitlik için, Hollanda Cumhuriyeti adına size bin altın dublon veriliyor!\nAyrıca, her deniz subayının hayalini süsleyen bu değerli seyir aletini de alacaksınız.";
			link.l1 = "Cumhuriyet'e hizmet etmekten mutluyum!";
			link.l1.go = "LucasAward_1";			
		break;
		
		case "LucasAward_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetActorType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
			sld.dialog.currentnode = "Bek_7";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			GiveItem2Character(pchar, "bussol");
		break;
		
		case "LucasAward_2":
			dialog.text = "Tebrikler tekrar, dostum. Ve lütfen, bir hafta sonra beni ziyaret et. Son derece hassas bir mesele için sana ihtiyacımız var.";
			link.l1 = "Anlaşıldı, Bay Rodenburg. Bir hafta içinde sizi ziyaret edeceğim.";
			link.l1.go = "LucasAward_3";			
		break;
		
		case "LucasAward_3"://наведем порядок
			LAi_SetActorType(pchar);
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-25");
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_ActorGoToLocator(sld, "goto", "goto6", "BekSitDown", -1);
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("LucasGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
			sld = characterFromId("Lucas");
			LAi_ActorGoToLocator(sld, "reload", "reload1", "LucasReturnInCabinet", -1);
			bDisableFastReload = true;
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			SetTimerFunction("GollandGambit_4_ZadanieStart", 0, 0, 7);
			AddSimpleRumourCity("They say that you were given a state award by Matias Beck himself! The Republic should be proud to have people like you, kapetein!", "Villemstad", 20, 4, "");
		break;
		
//--------------------------------------------------4 задание----------------------------------------------
		
		case "Abby":
			dialog.text = "Sana bir hikaye anlatayım. Bu, sıradaki görevinin ne kadar hassas olduğunu anlamana yardımcı olacak. Birkaç ay önce, İngiliz bayrağı altında Willemstad'a giden bir fluyt, merhum Jacob van Berg tarafından saldırıya uğradı. Gemiyi ele geçirdi ve haritalarımızda olmayan bir adanın yakınında batırdı. Fluyt'taki yolculardan sadece ikisi hayatta kaldı. Biri, Solomon Shneur adında bir Yahudi ve kızı Abigail. Diğer tüm yolcular, ailelerinin geri kalanı da dahil olmak üzere, hayatını kaybetti. Bu iki Yahudi, enkazdan bir parça üzerinde adaya ulaşmayı başardı.\nSolomon, yanında aile altınlarıyla dolu bir sandığı da sürüklemeyi başarmış. Gerçekten tasarruflu biriymiş. Hikayemizin bir diğer karakteri, Richard Fleetwood, yakınlarda seyrediyormuş ve çatışma seslerini duymuş. Van Berg'i yakalamak için geç kalmış ve 'Mirage' kaçmış. Fleetwood, adada hayatta kalan olup olmadığını kontrol etmeye karar vermiş.\nSolomon ve Abigail'i o ıssız adada kesin bir ölümden kurtarmış. Ne yazık ki yaşlı Solomon'un denizcilik gözü yokmuş. Richard'ın 'Valkerie'sini Jacob'ın 'Mirage'ı sanmış ve korsanın işi bitirmek için geri döndüğünden korkarak altınını adada bir yere saklamış. Sonuç olarak, kızıyla birlikte Fleetwood tarafından asıl varmak istedikleri yer olan Willemstad yakınlarındaki Blanca Lagoon'a, beş parasız bırakılmışlar.\nSolomon bana bu hikayeyi anlattı. Hollanda Cumhuriyeti, din özgürlüğünü destekler. Bu politikanın bir parçası olarak, Şirket burada Yahudi cemaatini destekliyor. Bu yüzden başlarını sokacak bir yerleri, yiyecekleri ve giyecekleri olduğundan emin oldum. Onları sık sık ziyaret ettim. Abigail... olağanüstü bir genç kadın. Samimi ve güven dolu.\nSana yalan söylemeyeceğim kaptan, onu istiyorum ve onunla evlenmeye niyetliyim. O da bana aşık, ama aramıza bir şey girdi.";
			link.l1 = "Babası damadının Yahudi olmamasından pek memnun değil mi?";
			link.l1.go = "Abby_0";			
		break;
		
		case "Abby_0":
			dialog.text = "Ha! Old Solomon would be in seventh heaven if I married Abigail, uncircumcised son-in-law or not. As a matter of fact, he urges her to accept my proposal. No, no, this is something that goes beyond Jew and Gentile. I ask you, my boy, to solve this problem for me. Talk to Abigail and find out what is wrong\nYou are a stranger; she might tell you things she would never reveal to familiar people because of her charming modesty. Shneur's house is located to the right of the company's office, if you stand with your back to it. I know that you are a smooth talker\nBut remember one thing: Richard Fleetwood was the true captain of the 'ghost ship'... Keep it in mind while talking to Abigail.";
			link.l1 = "Ha! Elbette hatırlıyorum onu, Bay Rodenburg. Sonuçta bu resmen kabul edilmiş bir gerçek, değil mi? O halde vakit kaybetmeyeceğim, hemen sevgilinize bir ziyarette bulunacağım.";
			link.l1.go = "Abby_1";			
		break;
		
		case "Abby_1":
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbyInHouse";
			AddQuestRecord("Holl_Gambit", "1-26");
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "Abby_2":
			dialog.text = "Gerçekten de Süleyman’ın altınını sakladığı adayı mı buldun? Harika! Artık her işi başarabileceğine inanmaya başlamıştım... Hazineyi karıştırırken başka bir şey buldun mu?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.ScullnotReturn"))
			{
				link.l1 = "Hayır, başka bir şey yok. Sadece para.";
				link.l1.go = "Abby_3";
			}
			else
			{
				link.l1 = "İlginç bir eşya vardı – yeşimden bir kafatası. Onu Solomon'a verdim, o da bunun aile yadigârı olduğunu söyledi. Ayrıca, onu ondan satın almayı düşündüğünü de belirtti...";
				link.l1.go = "Abby_4";
			}
		break;
		
		case "Abby_3":
			pchar.questTemp.HWIC.Holl.LucasItem = "obereg_11";
			dialog.text = "Hm. Peki öyle olsun. Yine de bu oldukça tuhaf. Neyse... Sana borçlandım, efendim, bunu asla unutmayacağım. Senin için bir ödül hazırladım - 50.000 peso ve bu muska. Artık senin.";
			link.l1 = "Teşekkür ederim, Bay Rodenburg!";
			link.l1.go = "Abby_5";
		break;
		
		case "Abby_4":
			pchar.questTemp.HWIC.Holl.LucasItem = "totem_04";
			dialog.text = "Mükemmel! Evet, bu eseri Solomon'dan satın alacağım, ona gerek yok ve benim için çok cömert bir alıcı var. Senin için bir ödül hazırladım - 50.000 peso ve bu muska. Artık senin.";
			link.l1 = "Teşekkür ederim, Bay Rodenburg!";
			link.l1.go = "Abby_5";
		break;
		
		case "Abby_5":
			dialog.text = "Şu anda senin gibi bir kaptana layık bir işim yok. Ama Curaçao'dan fazla uzaklaşma, yakında tekrar sana ihtiyacım olacak.";
			link.l1 = "Anladım, efendim. Hoşça kalın!";
			link.l1.go = "exit";
			GiveItem2Character(pchar, pchar.questTemp.HWIC.Holl.LucasItem);
			AddMoneyToCharacter(pchar, 50000);
			pchar.questTemp.HWIC.Holl = "Merdok_wait";
			AddQuestRecord("Holl_Gambit", "1-34");
			DelMapQuestMarkCity("Villemstad");
			SetTimerFunction("GollandGambit_5_ZadanieStart", 0, 0, 10);
			AddSimpleRumourCity("Have you heard the latest news? Mynheer Rodenburg is going to marry Abigail Shneur, the beautiful daughter of the old crazy Jew Solomon. What can I say, she is a lucky girl. God willing, she'll be baptized a true Christian before the wedding!", "Villemstad", 20, 3, "");
		break;
		
		case "Abby_6":
			dialog.text = "Ha, bu kadar mı? Tamamen saçma... tam da bir kadına yakışır bir hareket. Dinle beni evlat, bu sorun kolayca çözülebilir. Süleyman'ın sakladığı paranın miktarını biliyorum: 200.000 peso. Kendi ve Abigail'in mutluluğu için bu paradan vazgeçmeye hazırım. Parayı sana vereceğim ve sen de bir iki hafta için Curaçao'dan ayrılacaksın. Sonra geri dönüp Süleyman'a parayı vereceksin. Sanki parayı sen bulmuşsun gibi davranırsın. Kurt doyar, kuzuya da bir şey olmaz. Al, işte gereken miktar.";
			link.l1 = "İyi, sade bir plan. Hadi yapalım.";
			link.l1.go = "Abby_7";
		break;
		
		case "Abby_7":
			dialog.text = "Açık denize açıl ve on gün sonra bana geri dön. Git, faydalı bir şeyler yap. Manga Rosa'yı ara, malzeme üret, ya da başka bir şey yap.";
			link.l1 = "Ne derseniz deyin, Bay Rodenburg.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 200000);
			pchar.questTemp.HWIC.Holl = "GiveLucasMoney";
			SaveCurrentQuestDateParam("questTemp.HWIC.Holl.LucasMoney");
			pchar.questTemp.HWIC.Holl.LucasMoney = "true";
			AddQuestRecord("Holl_Gambit", "1-35");
		break;
		
		case "Abby_8":
			pchar.questTemp.HWIC.Holl.LucasItem = "obereg_11";
			dialog.text = "Harika! Bir kez daha işi mükemmel yaptınız. Size borçlandım, efendim, bunu asla unutmayacağım. Sizin için bir ödül hazırladım – 50.000 peso ve bu muska. Artık sizin.";
			link.l1 = "Teşekkür ederim, Bay Rodenburg!";
			link.l1.go = "Abby_5";
		break;
		
//-------------------------------------------5 задание-------------------------------------------------
		case "Merdok":
			dialog.text = "Evet, tam olarak öyle. Dostum, bazen kimin dostun, kimin düşmanın olduğunu ayırt etmek zor olabiliyor. Bazen en yakınındaki kişi ne zaman baş düşmanın olur, fark edemiyorsun. St. John's'tan ortak tanıdığımız John Murdock – ya da diğer adıyla Johan van Merden – Şirket'in eski bir ajanıydı, şimdi ise kendini İngiliz Donanması'na sattı.\nSon görevi ise Şirket'in en parlak yıldızlarından birini ortadan kaldırmak... yani seni.";
			link.l1 = "Bunu duymak hoşuma gitti. Söylemesen, hiç aklıma gelmezdi.";
			link.l1.go = "Merdok_1";
		break;
		
		case "Merdok_1":
			dialog.text = "Kesinlikle, kaptan. O tam bir tilki. O alçağı bul ve harekete geçmeden önce öldür. Antigua'ya git ve eczanesine gizli bir giriş ara. Kilisenin önünde gizli bir tünele açılan bir kapak var. Onu kullan.";
			link.l1 = "Ben hallederim.";
			link.l1.go = "Merdok_2";
		break;
		
		case "Merdok_2":
			dialog.text = "Bir şey daha, kaptan. Johan öldüğünde cesedini, evi ve bodrumu ara. Onun bir arşivi var—Şirket için çalışırken tuttuğu kalın bir defter, içine bizi mahvedecek notlar yazmış. Düşmanlarımızın eline geçerse hepimizi yok edecek bilgiler var içinde.\nO lanetli arşivi bulup bana getir, karşılığında fazladan ödeme alacaksın. Şimdi git. Yolun açık olsun, Kaptan "+pchar.name+", ve mümkünse sağ salim dönmeye çalış. Cumhuriyet sana ihtiyaç duyuyor!";
			link.l1 = "Sana söz veriyorum, efendim, tek parça halinde döneceğim. Bu kesinlikle benim de en çok işime gelen şey!";
			link.l1.go = "Merdok_3";
		break;
		
		case "Merdok_3":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "KillMerdok";
			AddQuestRecord("Holl_Gambit", "1-42");
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			bDisableFastReload = false;
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);//откроем проход в подземелье из дома
			LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false);//откроем проход в дом из подземелья
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//аптеку закроем
			pchar.quest.Merdok_inCave.win_condition.l1 = "location";
			pchar.quest.Merdok_inCave.win_condition.l1.location = "SentJons_TownCave";
			pchar.quest.Merdok_inCave.function = "MerdokInUndergroundCave";
			LAi_LocationDisableOfficersGen("SentJons_TownCave", true);//офицеров в шахту не пускать
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("SentJons", false);
		break;
		
		case "Merdok_4":
			dialog.text = "Mükemmel, kaptan! Gerçekten çok memnun oldum. Arşivini bulabildin mi?";
			if (CheckCharacterItem(pchar, "MerdokArchive"))//архив
			{
				link.l1 = "Evet, işte burada. Eczacının cesedinde ya da sandıklarında başka hiçbir belge yoktu.";
				link.l1.go = "Merdok_book";
			}
			link.l2 = "Hayır. Her yerde aradım ama hiçbir şey bulamadım.";
			link.l2.go = "Merdok_5";
			DeleteAttribute("SentJons_TownCave", "box2");//если не нашли шифр - уже и не найдем
		break;
		
		case "Merdok_5":
			dialog.text = "Bu kesinlikle yazık, ama benim için sorun değil. Eminim Johan'ın onu İngilizlere vermeye vakti olmamıştır, yoksa şimdiye kadar çoktan boynumuza ilmek geçirilmişti... Muhtemelen onu gizli bir yere sakladı... orada sonsuza dek kalsın! Görevimizi başarıyla tamamladığınız için sizi tebrik ederim, kaptan!";
			link.l1 = "Şükranlarımı sunarım!";
			link.l1.go = "Merdok_6";
			
			SetTimerCondition("PZ_LigaInJungle", 0, 0, 7, false);	// проверку не прошёл, значит нападёт Лига через неделю, после чего начнётся таймер на 30 дней 1 этапа
		break;
		
		case "Merdok_book":
			dialog.text = "Harika! Şimdi olması gereken yerde, güvende. Bir kez daha en iyisi olduğunu kanıtladın... Kitabı bana ver... Arşiv için bir ödül var - bu güzel tüfek. Bana yıllarca iyi hizmet etti, şimdi senin!";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.PZ_RodenburgUkradenaStranitsa"))
			{
				link.l1.go = "Merdok_book_2";
			}
			else
			{
				link.l1.go = "Merdok_book_6";
			}
			RemoveItems(PChar, "MerdokArchive", 1);
		break;
		
		case "Merdok_book_2":
			dialog.text = "Ne yapmaya çalışıyorsun, Kaptan? Birkaç sayfa eksik - hem de benim için çok önemli sayfalar. Fark etmeyeceğimi mi sandın, böylece onları bana karşı kullanabilecektin? Yoksa bundan daha fazlasını mı umuyordun? Korkarım, ikisinde de seni hayal kırıklığına uğratacağım.";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l1 = "(Güvenilir) Özür dilerim. Tek hatam arşivi önceden kendim kontrol etmemekti.";
				link.l1.go = "VD_Merdok_book_3";
				SetTimerCondition("PZ_Etap1_Start", 0, 0, 30, false);	// 1 этап стартует через 30 дней
			}
			else
			{
				Notification_Perk(false, "Trustworthy");
				link.l1 = "Gerçekten de sayfaları koparıp, sonra arşivi umursamaz bir tavırla teslim eder miydim?";
				link.l1.go = "Merdok_book_3";
				SetTimerCondition("PZ_LigaInJungle", 0, 0, 7, false);	// проверку не прошёл, значит нападёт Лига через неделю, после чего начнётся таймер на 30 дней 1 этапа
			}
			LAi_Fade("", "");
		break;
		
		case "Merdok_book_3":
			dialog.text = "Açgözlülük, aptallık ve küstahlık bazen insanları en çılgınca işlere sürükler, Kaptan.";
			link.l1 = "Bu üçünün hiçbiri beni motive etmedi, emin olabilirsin.";
			link.l1.go = "Merdok_book_4";
		break;
		
		case "Merdok_book_4":
			dialog.text = "Yani diyorsun ki, van Merden o sayfaları çıkartıp başka bir yere mi saklamış?";
			link.l1 = "Kesinlikle. Geri dönüp onları arayabilirim—eczaneyi altüst ederim, gerekirse bütün St. John's'u da—eğer gerekli görüyorsanız.";
			link.l1.go = "Merdok_book_5";
		break;
		
		case "Merdok_book_5":
			dialog.text = "Gerek yok, efendim. Zaten önemli olanların çoğu burada, eksik sayfalar olmadan gerisi bana bir tehdit oluşturmaz.";
			link.l1 = "";
			link.l1.go = "Merdok_book_6";
		break;
		
		case "VD_Merdok_book_3":
			dialog.text = "Yani, bu bir ilgisizlik ya da meraksızlık meselesi, yoksa bir sahtekârlık ya da gizli bir niyet değil mi? Sence sen bulduğunda da zaten böyle miydi?";
			link.l1 = "Büyük ihtimalle, Bay Rodenburg. Belki de van Merden o sayfaları önceden koparmıştır. ";
			link.l1.go = "VD_Merdok_book_4";
		break;
		
		case "VD_Merdok_book_4":
			dialog.text = "Belki de en iyisi böyle. O sayfalar olmadan, arşivin geri kalanı bana hiçbir tehdit oluşturmaz – hele ki cahil ellerde.";
			link.l1 = "";
			if (IsCharacterPerkOn(pchar, "Trustworthy")) link.l1.go = "Merdok_book_6";
			else link.l1 = "Merdok_6";
		break;
		
		case "Merdok_book_6":
			dialog.text = "Arşiv için bir ödül var - bu güzel tüfek. Bana büyük hizmet etti, şimdi ise senin!";
			link.l1 = "Bedankt!";
			link.l1.go = "Merdok_6";
			GiveItem2Character(PChar, "mushket2");
		break;
		
		case "Merdok_6":
			dialog.text = "Seninle iyi iş çıkardık, kaptan. Abartısız söyleyebilirim ki, bunların hiçbiri sensiz olmazdı. Cumhuriyet'e hizmet etmeye devam edersen kariyerinde inanılmaz yerlere gelebilirsin, belki de soyluluk bile alırsın.";
			link.l1 = "Sanırım bu bir veda, Bay Rodenburg.";
			link.l1.go = "Merdok_7";
		break;
		
		case "Merdok_7":
			dialog.text = "Hoşça kal, "+pchar.name+". Burada yapmak istediğim her şeyi başardım, bu yüzden bir hafta içinde eve, Amsterdam'a dönüyorum. Yeni eşim Abigail ve kayınpederim Solomon bana eşlik edecekler. Peter Stuyvesant zaten yeni bir Şirket başkan yardımcısı buldu, bu yüzden bir şeye ihtiyacın olursa onunla konuş\nHizmetlerin için sana Meifeng'i veriyorum. Artık o senin, kaptan, bunu hak ettin.";
			link.l1 = "Teşekkür ederim, Bay Rodenburg. Meifeng'e gerçekten alıştım ve onu şimdiden kendi gemim gibi görmeye başladım.";
			link.l1.go = "Merdok_8";
		break;
		
		case "Merdok_8":
			dialog.text = "Ve şimdi senden beni yalnız bırakmanı istemek zorundayım, oğlum. Denize açılmadan önce yapmam gereken çok iş var... Bir gün Amsterdam'da beni ziyaret et! Birlikte bir kadeh içer, eski güzel günleri yad ederiz...";
			link.l1 = "Evet, efendim. Umarım yeni hayatınızda hepiniz mutlu ve refah içinde olursunuz! Elveda!";
			link.l1.go = "Merdok_9";
			// belamour legendary edition -->
			link.l2 = "Evet, efendim. Umarım yeni hayatınızda hepiniz mutlu ve refah içinde olursunuz!\n(dişlerini sıkarak) ... Umarım bir daha karşılaşmayız, kibirli herif. Sadece bekle, o 'utangaç' Yahudi cadısıyla evli olmanın ne kadar keyifli olduğunu keşfettiğinde göreceksin.";
			link.l2.go = "Merdok_9a";
		break;
		
		case "Merdok_9a":
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			DialogExit();
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			AddQuestRecord("Holl_Gambit", "1-41");
			CloseQuestHeader("Holl_Gambit");
			sld = characterFromId("Abigile");//уберем Аби
			sld.lifeday = 0;
			sld = characterFromId("Solomon");//уберем Соломона
			sld.lifeday = 0;
			pchar.quest.Lucas_quit.win_condition.l1 = "Timer";
			pchar.quest.Lucas_quit.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Lucas_quit.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Lucas_quit.function = "LucasQuit";//прерывание на Лукаса
			pchar.questTemp.HWIC.Detector = "holl_win";
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddSimpleRumourCity("Mynheer Rodenburg has sailed to Amsterdam with his young wife and father-in-law. Are you the new vice-director?", "Villemstad", 30, 3, "");
			AddSimpleRumour("They say, kapitein, that you are well regarded by the governor-general. Mynheer Rodenburg supposedly appointed you as his successor in the Company, is that so?", HOLLAND, 30, 3);
		break;
		
		case "Merdok_9":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			DialogExit();
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			AddQuestRecord("Holl_Gambit", "1-41");
			CloseQuestHeader("Holl_Gambit");
			sld = characterFromId("Abigile");//уберем Аби
			sld.lifeday = 0;
			sld = characterFromId("Solomon");//уберем Соломона
			sld.lifeday = 0;
			pchar.quest.Lucas_quit.win_condition.l1 = "Timer";
			pchar.quest.Lucas_quit.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Lucas_quit.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Lucas_quit.function = "LucasQuit";//прерывание на Лукаса
			pchar.questTemp.HWIC.Detector = "holl_win";
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddSimpleRumourCity("Mynheer Rodenburg has sailed to Amsterdam with his young wife and father-in-law. Are you the new vice-director?", "Villemstad", 30, 3, "");
			AddSimpleRumour("They say, kapitein, that you are well regarded by the governor-general. Mynheer Rodenburg supposedly appointed you as his successor in the Company, is that so?", HOLLAND, 30, 3);
		break;
		
//----------------------------------------------за Англию------------------------------------------------------
		case "Lucas_abordage":
			dialog.text = "Tanrı aşkına! Fleetwood'un köpeği! Bugün kazanabilirsin, ama Lucas Rodenburg hayatını ucuza satmayacak.";
			link.l1 = "Bence hiç de öyle değil. Hayatını bana bedavaya teslim edeceksin, seni Hollandalı cimri.";
			link.l1.go = "Lucas_abordage_1";
		break;
		
		case "Lucas_abordage_1":
			PlaySound("Voice\English\hambit\Lucas Rodenburg-04.wav");
			dialog.text = "Cehennemin dibinden gelip ağzına sıçacağım! Az önce ambarı ateşe verdim, yangın birazdan barut mahzenine de sıçrayacak! Gemilerimiz birbirine kenetlenmiş, kaçış umudu yok! Ya yanacaksın ya da köpekbalıklarına yem olacaksın!";
			link.l1 = "Lanet olsun! Geri çekilin, adamlar, geri çekilmeliyiz!";
			link.l1.go = "Lucas_abordage_2";
			// belamour legendary edition -->
			link.l2 = "Ruhun bedenini terk edene kadar buradan ayrılmam. Kımıldama, bu canını yakacak.";
			link.l2.go = "Lucas_abordage_2a";
		break;
		
		case "Lucas_abordage_2a":
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom1"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
		case "Lucas_abordage_2":
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom1"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
//----------------------------------------------против всех--------------------------------------------------
		case "LucasPrisoner":
			dialog.text = "Burada ne işin var, seni alçak? Dalga geçmeye mi geldin? Belki de sonunda bu oyundaki rolünü anlatırsın. Brigantinayı ele geçiren sendin, değil mi? Başından beri planın bu muydu?";
			link.l1 = "Buraya bir mesaj getirdim, Lucas Rodenburg. Seni aldattığın John Merdock’tan selamlar. Sen bana verilen görevdin ve ben onu tamamladım. Şimdilik hoşça kal.";
			link.l1.go = "LucasPrisoner_1";
		break;
		
		case "LucasPrisoner_1":
			PlaySound("Voice\English\hambit\Lucas Rodenburg-04.wav");
			dialog.text = "Johan? Haha! Demek tüm bunların arkasındaki adam oymuş! O eski düzenbaz! Ama oyun henüz bitmedi. Jacob van Berg sana geliyor ve kaçamayacaksın! Sen ve gemin artık bizim, zavallı deniz serserisi!";
			link.l1 = "Nefesini darağacı mahkemesi için sakla, Rodenburg.";
			link.l1.go = "LucasPrisoner_2";
		break;
		
		case "LucasPrisoner_2":
			DialogExit();
			pchar.questTemp.jailCanMove = true; //разрешить пройти мимо стражи
			LAi_SetPlayerType(pchar);
			pchar.quest.Login_Joakim.win_condition.l1 = "location";
			pchar.quest.Login_Joakim.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Login_Joakim.function = "Create_Joakim";
			pchar.questTemp.HWIC.Self = "JoakimMeeting";
			SetFunctionTimerCondition("LucasQuit", 0, 0, 7, false);
		break;
	}
}
