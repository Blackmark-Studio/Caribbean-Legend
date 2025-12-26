void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, n;
	string sTemp, sStr, sStr2, sGun, sBullet, attrL;
	
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
			dialog.text = "Ne istiyorsunuz?";
			link.l1 = "Hiçbir şey.";
			link.l1.go = "exit";
		break;
		
		case "Alonso":
			NextDiag.TempNode = "Alonso";
			
			// --> Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = "...";
				Link.l1 = "Alonso, seninle konuşmam lazım.";
				Link.l1.go = "SharlieEpilog_Alonso_1";
				break;
			}
			// эпилог <--

			if (GetDLCenabled(DLC_APPID_1))
			{
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.FirstStage", "ready"))
				{
					dialog.text = "Konuşabilir miyim, kaptan?";
					link.l1 = "Sonra görüşürüz, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Devam et.";
					link.l2.go = "Alonso_1";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.SecondStage", "ready"))
				{
					dialog.text = "Konuşabilir miyim, kaptan?";
					link.l1 = "Sonra görüşürüz, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Devam et.";
					link.l2.go = "Alonso_Lvl_8_Start";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.ThirdStage", "ready"))
				{
					dialog.text = "Konuşabilir miyim, kaptan?";
					link.l1 = "Sonra görüşürüz, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Devam et.";
					link.l2.go = "Alonso_Lvl_12_Start";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.FourthStage", "ready"))
				{
					dialog.text = "Konuşabilir miyim, kaptan?";
					link.l1 = "Sonra görüşürüz, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Devam et.";
					link.l2.go = "Alonso_Lvl_16_Start";
					break;
				}
			}
			
			dialog.text = " Bildirilecek bir şey yok, kaptan.";
			link.l1 = "Olduğun gibi kal, Alonso.";
			link.l1.go = "exit";
		break;
		
		case "Alonso_1":
			DelLandQuestMark(npchar);
			dialog.text = "Nasıl dayanıyorsun?";
			link.l1 = "Ne demek istiyorsun?";
			link.l1.go = "Alonso_2";
		break;
		
		// Основная развилка стадии 1
        case "Alonso_2":
            dialog.text = "Sen bu Karayip sularında aylardır yol alıyorsun, oysa bazıları burada bir haftayı bile çıkaramıyor. Mürettebat sana saygı duyuyor, orası kesin, ama ben mi? Senin için ileride ne var diye endişeleniyorum.\n"+"Düşüncelerini bizimle paylaş, kaptan. Tayfaya bir iyilik yap. Nerede "+pchar.ship.name+" nereye gidiyorsun?";
                          
            link.l1 = "Bir planım yok. Önce etrafı görmek istiyorum. Macera zaten bizi kendi bulur.";
            link.l1.go = "Alonso_Choice_1";
            
            link.l2 = "Bu sularda avcılar çok, Alonso. Ve "+pchar.ship.name+" en küçüğü bu. Şimdilik.";
            link.l2.go = "Alonso_Choice_2";
            
            link.l3 = "Para kazanmayı severim. Tercihen yasal yollardan. Ama nasıl olacak, göreceğiz.";
            link.l3.go = "Alonso_Choice_3";
			
            if (!SandBoxMode)
            {
                link.l4 = "Hikayeyi biliyorsun. O unutulmaz Ulysses sohbetinden sonra her şey daha da karmaşıklaştı...";
                link.l4.go = "Alonso_Choice_4";
            }
        break;
        
        case "Alonso_Choice_1":
            dialog.text = "İşte özgürlük bu! Sadece gemiyi idare edecek kadar paran olduğundan ve kötü günler için sandıkta biraz birikim bıraktığından emin ol.\n"+"Keyfin, görevin ya da hazine haritan seni nereye götürürse götürsün - yolcu taşımacılığı, yük taşımacılığı, karşına çıkan her türlü işi üstlenebilirsin.\n"+"Ufak tefek ticarete de bulaşmakta zarar yok - ucuz bulduğunda al, satabileceğin yerde sat.\n"+"Ve yol boyunca yalnız bir tüccar gemisi görürsen... Heh. Dediğin gibi, kaptan. Macera bizi bulacak, hiç şüphe yok.";
            
            AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 50);
            AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 50);
            AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 50);
            
            link.l1 = "İyi tavsiyen için teşekkürler, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_2":
            dialog.text = "Karlı bir iş, eğer gemin buna dayanabilirse. Yalnız tüccarları bul ve onlara 'ucuza kaçmak, pahalıya patlar' ne demekmiş göster.\n"+"Ne yazık ki, senin için başka bir deyiş daha var: 'Gerçek er geç ortaya çıkar.' Mürettebattan biri mutlaka ilk limanda senin maceralarını ağzından kaçıracaktır.\n"+"Yani ya herkesi biraz soyacaksın, ya da ömür boyu bir düşman bayrağı seçeceksin.\n"+"Belki de biraz acele ediyorum. İşler gerçekten sarpa sararsa, Port Royal'da doğru parayı verirsen yetkililerle aranı düzeltecek bir avukat var. Buna korsanlık vergisi diyelim, heh-heh!";
            
            AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 50);
            AddCharacterExpToSkill(pchar, SKILL_ACCURACY, 50);
            ChangeCharacterComplexReputation(pchar, "nobility", -1);
            
            link.l1 = "İyi tavsiyen için teşekkürler, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_3":
            dialog.text = "Eh, orada sana pek yardımcı olamam, kaptan. Sana düzgün bir ticaret gemisi lazım – bir barquentine, ya da daha iyisi bir barque. Bunu söylediğime pişman olacağım ama, en iyisi hafif toplar tak ya da topçuları tamamen bırak.\n"+"Dükkan sahiplerinden yük taşıma sözleşmeleri al, yol boyunca kendi hesabına ticaret yap ve yolcuları taşı.\n"+"Yeterince para biriktirdiğinde, dükkanlara ve bankalara yatırım yap. Unutma kaptan, bir gün paran kendi kendine para kazandırmaya başlayacak ve yüzlerce adamla birlikte gerçek bir gemi alabilecek hale geleceksin.\n"+"Bu arada, bunun bedelini sen değil, işin ödeyecek.";
            
            AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 50);
            AddCharacterExpToSkill(pchar, SKILL_SAILING, 50);
            ChangeCharacterComplexReputation(pchar, "nobility", 1);
            
            link.l1 = "İyi tavsiyen için teşekkürler, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_4":
            dialog.text = "Ben farklı düşünüyorum, kaptan. Ulysses'te sadece bir yolcuydun – o zavallıların kaderleri üzerinde hiçbir söz hakkı yok. Şimdi ise şapkasını hak etmiş bir kaptansın, bu da demek oluyor ki her türlü sorunu çözebilirsin. Sana daha önce de söyledim – bizim dünyamızda bundan daha yüksek bir makam yok.\n"+"İçimde bir his var, bu kardeşinle olan hikaye yıllarca sürecek gibi, o yüzden önce kendine dikkat et. Monsieur Michel bir yere gitmiyor, heh-heh...\n"+"Karayipler'de sorunları olan tek kişi sen değilsin. Başkalarına yardım ederek para, ekipman ve bağlantılar kazanmak için mükemmel bir zaman. Bu aile işinde ihtiyacın olacak her şeyi yol boyunca öğreneceksin...";
            
            AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 100);
            ChangeCharacterComplexReputation(pchar, "nobility", 1);
            
            link.l1 = "İyi tavsiyelerin için teşekkürler, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
		
        case "Alonso_Common_End":
            dialog.text = "Kendini tek bir role hapsetme, kaptan. Ne zaman istersen, ne istersen yap. Her şeyi al, hiçbir şey geri verme. Gayet iyi idare edersin.";
            link.l1 = "Ve verdiğin akıl için de teşekkürler.";
            link.l1.go = "Alonso_Common_End_2";
        break;
        
        case "Alonso_Common_End_2":
            dialog.text = "Eh, bunun için bana para ödüyorsun, kaptan. Mürettebatın senin emirlerine sadece o cılız maaşları için uyduğunu mu sanıyorsun?\n"+"Bir gemide onlarca adam, daracık bir alana tıkılmış, bir daha ne zaman karaya ayak basacaklarını ya da hiç basıp basamayacaklarını bilmeden yaşar. Bir gemiyi batırmak mı? Fazla kolay.";
            link.l1 = "Evet, evet, bu konuşmayı daha önce de duydum, Alonso. Gemiler hakkında ne diyordun?";
            link.l1.go = "Alonso_Common_End_3";
        break;
        
        case "Alonso_Common_End_3":
            dialog.text = "Heh! Bir gemi hem bir hapishane, hem bir ordu kampı, hem de bir manastır gibidir. Kısacası, bir grup adamın bir araya gelmesidir. Sorunlar ya sözle ya da kırbaçla çözülür. Senin durumunda, ikincisi, heh-heh, pek mümkün değil, o yüzden seninle biraz konuşalım dedim. İşini kolaylaştıralım, hani.";
            link.l1 = "Hiç hapis yattın mı? Orduda bulundun mu? Ya da Tanrı korusun, bir manastırda? Düşününce, Alonso, bana biraz kendinden bahsetsene. Senin hakkında neredeyse hiçbir şey bilmiyorum.";
            link.l1.go = "Alonso_Story_1";
        break;
        
        // История Алонсо
        case "Alonso_Story_1":
            dialog.text = "Doğrusunu söylemek gerekirse, manastırlardan hep uzak durdum. Ama bir zamanlar Kutsal Engizisyon'da görev yapmışlığım var...";
            link.l1 = "Tanrı aşkına, bu nasıl oldu?";
            link.l1.go = "Alonso_Story_2";
        break;
        
        case "Alonso_Story_2":
            dialog.text = "Ah! Şöyle oldu. Avrupa savaşında paralı askerlik yapıyordum. Şeytan bilir nasıl başladı, kim kiminle savaşıyordu. Bildiğimiz tek şey, savaş otuz yıldır sürüyordu ve hangi komutanların ödemeleri az çok düzenli yaptığıydı. İşte asıl macera buydu!\n"+"Bu '42'deydi... ya da '41 miydi? Fark etmez. İmparator'un hizmetindeki iki birlik, ormanda karşılaştı. Siste. Ve birbirlerini doğramaya başladılar! Üç gün süren bir katliam!";
            link.l1 = "Bu nasıl mümkün olabilir?";
            link.l1.go = "Alonso_Story_3";
        break;
        
        case "Alonso_Story_3":
            dialog.text = "O sisteyi düşün, o sisin içinde dostu düşmandan ayırt etmek mümkün mü? Üstelik üç aydır maaş almamıştık, herkesin aklında ganimet vardı.\n"+"Birbirimizi neredeyse yarı yarıya öldürdük. Ne olup bittiğini anladığımızda ise çok geçti. İşte o zaman bu Moskvalı ile tanıştım. Ayı gibi iri, ama altın gibi bir kalbi var!";
            link.l1 = "Sonra ne oldu?";
            link.l1.go = "Alonso_Story_4";
        break;
        
        case "Alonso_Story_4":
            dialog.text = "Savaşta nasıl olduğunu bilirsin ya? İlk haber veren kahraman olur. Biz de düşündük ki - bu felaketi kendi lehimize çevirelim dedik!\n"+"Adamları topladık, maaşçının yanına gittik, 'şanlı bir savaşı' rapor ettik. Ölenlerin parası kesildi, sağ kalanlar ödendi, ben ve arkadaşım prim aldık, komutan da payını aldı.";
            link.l1 = "Demek zenginsin, Alonso.";
            link.l1.go = "Alonso_Story_5";
        break;
        
        case "Alonso_Story_5":
            dialog.text = "Ha! Bir hafta boyunca şarap içip iskambil oynadık. Şansıma, karlı Moskova'dan yeni dostumun nadir süs eşyalarına zaafı vardı, yoksa borçlar hapishanesine düşerdim. Benden bir ödül aldı - muhteşem üç namlulu bir tabanca, hem de iyi bir fiyata. Talihsizliğimden faydalanmadı.";
            link.l1 = "Bu gerçekten ilginç bir hikaye, Alonso. Bana kalırsa bunu uydurdun gibi geliyor.";
            link.l1.go = "Alonso_Gift";
        break;
        
        // Вручение подарка
        case "Alonso_Gift":
            dialog.text = "Beni kırdın, kaptan. Al, bu küçük hediyeyi kabul et.";
            link.l1 = "Ne oldu?";
            link.l1.go = "Alonso_Gift_2";
        break;
        
        case "Alonso_Gift_2":
            // Выдаем Берендейку
            GiveItem2Character(pchar, "talisman20");
			SetAlchemyRecipeKnown("talisman20");
            
            dialog.text = "Tüfekle savaşmak için bir bandolyer. Moskova’lı arkadaşımın memleketinde herkes bunları takarmış. En azından o öyle söyledi.\n"+"Sana iyi hizmet etsin, kaptan. Bunu mürettebatın bir hediyesi olarak kabul et.";
            link.l1 = "Beklenmedik oldu! Teşekkür ederim, Alonso. Peki Engizisyon’daki o hizmet neydi?";
            link.l1.go = "Alonso_Escape";
        break;
        
        case "Alonso_Escape":
            PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "Eh...\n"+"Çanlar çalıyor, kaptan! İşe dönme vakti. Başka bir zaman devam ederiz.";
            link.l1 = "Bu sohbeti kesinlikle sürdüreceğiz. Hediye için teşekkürler!";
            link.l1.go = "exit";
            
			AddDialogExitQuestFunction("LoyaltyPack_FirstStage_DlgExit");
        break;
		
		// (Level 8) - Continuing the story
        case "Alonso_Lvl_8_Start":
			DelLandQuestMark(npchar);
			dialog.text = "Son konuşmamızdan bu yana çok şey başardın, artık ne tayfa ne de ben yeteneklerinden şüphe ediyoruz.";
			link.l1 = "Şüpheler mi vardı?";
			link.l1.go = "Alonso_Lvl_8_1";
        break;

        case "Alonso_Lvl_8_1":
            dialog.text = "Elbette vardı. Biz sade insanlarız – en kötüsüne hazırlıklı oluruz. Özgürlüğünün tadını çıkar, kaptan. Böyle devam edersen Karayipler’in bambaşka bir yüzünü göreceksin.";
            link.l1 = "Bunu duymak güzel. Şimdi Engizisyondaki hizmetini anlat bana. Geçen sefer bir ordu hikayesiyle başlamıştın ve yine onunla bitirmiştin.";
            link.l1.go = "Alonso_Lvl_8_2";
        break;

        case "Alonso_Lvl_8_2":
            dialog.text = "Anlatacak ne var ki? O anlamsız ama oldukça kârlı orman katliamından sonra, ben ve Moskof birbirimize çok ısındık ve daha birçok iş çevirdik.\n"+"Bir keresinde imparatorluğun erzak kervanına baskın yapmaya karar verdiğimizi hatırlıyorum. Gözcüler, ganimet, altın, silah taşıdıklarını söylemişti...";
            link.l1 = "Peki, başardın mı?";
            link.l1.go = "Alonso_Lvl_8_3";
        break;

        case "Alonso_Lvl_8_3":
            dialog.text = "Çocuk oyuncağıydı. İki taraftan saldırdık, nöbetçileri dağıttık, vagonları açtık - ve karşımıza çıkan lahana oldu! Çürük, pis kokulu lahana; bir garnizonun yiyeceği! Ama biliyor musun? Bir haftadır açtık, o yüzden buna bile sevindik!";
            link.l1 = "Gemideki yemek sanki daha mı iyi.";
            link.l1.go = "Alonso_Lvl_8_4";
        break;

        case "Alonso_Lvl_8_4":
            dialog.text = "Artık alıştım buna. Ama o zamanlar... Bir hafta boyunca yiyecek aradıktan sonra, ağaçların kabuğunu kemirirdin!\n"+"Ama arkadaşım yılmadı. Özel karışımından bir matara çıkardı – Moskova usulüymüş, öyle dedi. Ne olduğu umurumuzda değildi, sirke olmadığı sürece! Birkaç yudumdan sonra, o lahana bile ziyafet gibi geldi!";
            link.l1 = "İğrenç.";
            link.l1.go = "Alonso_Lvl_8_5";
        break;

        case "Alonso_Lvl_8_5":
            dialog.text = "İğrenç olan şey su fıçılarımızın haliydi, ama o Moskof içkisi o gün hayatımı kurtardı.";
            link.l1 = "Nasıl yani?";
            link.l1.go = "Alonso_Lvl_8_6";
        break;

        case "Alonso_Lvl_8_6":
            dialog.text = "Tam oracıkta, yolun çamurunda, etrafımızda lahanalar yüzerken körkütük sarhoş olduk. Sonra, işte, laf lafı açtı ve bir soyluyla tartışmaya girdim. Alman biriydi, çok düzgün, çok kuralcı. Bizimle içmeye tenezzül etmedi, oturup tüfeğini temizledi ve alaycı laflar etti durdu.\n"+"Yani orada oturuyoruz, lahanayla dertlerimizi boğuyoruz. Sonra başladı bize askeri bilgelik dersi vermeye. Diyor ki, güvendiğimiz kılıçlar ve mızraklar yakında unutulacakmış, ama süngü... işte asıl gelecek oymuş, her şeyin anahtarıymış."+"Yani, onunla tartıştım ve nasıl olduysa ölümüne dövüşmeye karar verdik – hem de süngülerle. Nasıl oldu diye sorma, ben de hatırlamıyorum.\n"+"Ama bütün bölüğümüzde sadece iki süngü vardı. Biri o ufak tefek subaya aitti, diğeri ise İngiliz Fox'a. Onun tüfeğini ödünç aldım ve Alman'ı onunla döve döve öldürdüm, sonra da ortadan kayboldum.";
            link.l1 = "Ama hem aç hem de sarhoştun.";
            link.l1.go = "Alonso_Lvl_8_7";
        break;

        case "Alonso_Lvl_8_7":
            dialog.text = "Sonradan anladım ki, arkadaşımın içkisi ağır bir tüfeği sallarken insanın elini gerçekten sabit tutuyor. Artık ölü Alman’ın fikirlerine katılmaya daha meyilliyim.";
            link.l1 = "Ve bu, Engizisyon'daki hizmetinle nasıl bağlantılı?";
            link.l1.go = "Alonso_Lvl_8_Gift";
        break;

        case "Alonso_Lvl_8_Gift":
            dialog.text = "Bana yine inanmıyorsun, kaptan! Al, bunu da al.";
            link.l1 = "Bir şişe ve bir parça kağıt mı?";
            link.l1.go = "Alonso_Lvl_8_Gift_2";
        break;

        case "Alonso_Lvl_8_Gift_2":
            // Даём игроку настойку и рецепт
            GiveItem2Character(pchar, "vodka");
            SetAlchemyRecipeKnown("vodka");

            dialog.text = "İşte sana bahsettiğim içki bu. Ve tarifi de burada. Beğenirsen diye, heh-heh.";
            link.l1 = "Üzgünüm dostum, ama karalamalar ve bulanık bir karışım yetmez...";
            link.l1.go = "Alonso_Lvl_8_Gift_3";
        break;

        case "Alonso_Lvl_8_Gift_3":
            // Даём игроку мушкет с багинетом
            GiveItem2Character(pchar, "mushket10");

            dialog.text = "Pekâlâ, pekâlâ, kaptan. Bunu sana zaten verecektim. Bu tür bir silah bana göre değil, ama senin işine yarar. Süngüler nadir bulunur. Ama bir kere kullanmayı öğrendin mi, kılıç sallamayı unutursun.";
            link.l1 = "Dur bir dakika, bu gerçekten o imparatorluk subayının tüfeği mi? Hani öldürdüğün adamın?";
            link.l1.go = "Alonso_Lvl_8_Gift_4";
        break;

        case "Alonso_Lvl_8_Gift_4":
			PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "Aynen öyle. Gördüğün gibi, sana doğruyu söyledim, kaptan.";
            link.l1 = "Ama ben bundan bahsetmedim.";
            link.l1.go = "Alonso_Lvl_8_Escape";
        break;

        case "Alonso_Lvl_8_Escape":
            dialog.text = "Çanlar çalıyor, kaptan! İşe dönme vakti. Sonra devam ederiz.";
            link.l1 = "Bu konuşmayı kesinlikle sürdüreceğiz. Tüfek için teşekkürler!";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("LoyaltyPack_SecondStage_DlgExit");
        break;

        // (Уровень 12)
        case "Alonso_Lvl_12_Start":
			DelLandQuestMark(npchar);
			dialog.text = "Kaptan, yeni askerlerle ilgili...";
			link.l1 = "Bir şey mi oldu?";
			link.l1.go = "Alonso_Lvl_12_1";
        break;

        case "Alonso_Lvl_12_1":
            dialog.text = "Bu akşamki ayinde, yeni askerlerden biri özellikle sizin geminize katılmak istediğini söyledi.";
            link.l1 = "Ve bu tam olarak ne anlama geliyor?";
            link.l1.go = "Alonso_Lvl_12_2";
        break;

        case "Alonso_Lvl_12_2":
            dialog.text = "Yakında onun gibi başkaları da olabilir. Artık bir adın var, kaptan.";
            link.l1 = "Hâlâ adının ardındaki hikayeyi bilmiyor olmam komik. Engizisyon'la ilgili o hikayeyi hiç tamamlamadın.";
            link.l1.go = "Alonso_Lvl_12_3";
        break;

        case "Alonso_Lvl_12_3":
            dialog.text = "Ah, nerede kalmıştım... Evet! Sonra askeri tedarikçi olmaya karar verdik. Savaş sona eriyordu, geleceği düşünmek gerekiyordu. Ve arkadaşımın kafası her zaman gelecekle ilgili düşüncelerle doluydu.";
            link.l1 = "Bu gerçekten büyük bir kariyer sıçraması. Daha dün, yağmalanmış bir lahana arabasının yanında sarhoş oluyordun.";
            link.l1.go = "Alonso_Lvl_12_4";
        break;

        case "Alonso_Lvl_12_4":
            dialog.text = "Dur, daha da güzelleşiyor. Bir alay için yüz miğfer siparişi aldık. Üstelik güzel bir avans da verdiler. Biz de kutladık... Kart oynadık falan.\n"+"Sabah uyanıyorsun --- para yok, ordu iki gün sonra yola çıkıyor, ve hâlâ yüz miğfer teslim etmemiz gerekiyor!";
            link.l1 = "Peki   ne yaptın?";
            link.l1.go = "Alonso_Lvl_12_5";
        break;

        case "Alonso_Lvl_12_5":
            dialog.text = "Taze savaş alanına gittim, ölülerden şapkaları topladım. Sonra üzerine türlü türlü metal parçaları çaktım, plakalar ekledim... Komik görünüyordu ama işe yaradı! Kesinlikle bir kılıç darbesinden kurtarır. En azından bir kez, garanti. Herhangi bir miğfer kadar iyi, değil mi?!";
            link.l1 = "Çeyrekbaşı senin zekânı takdir etti mi?";
            link.l1.go = "Alonso_Lvl_12_6";
        break;

        case "Alonso_Lvl_12_6":
            dialog.text = "Bizi zimmete para geçirme ve dolandırıcılıkla mahkemeye verdiler. Ama biliyor musun? Sonradan öğrendik ki, o şapkalar birden fazla kez hayat kurtarmış. Bizimkini de, sonunda anlaşıldı.";
            link.l1 = "Nasıl yani?";
            link.l1.go = "Alonso_Lvl_12_7";
        break;

        case "Alonso_Lvl_12_7":
            dialog.text = "İkimiz de hapse atıldık. Birliğimiz ise bir göreve gönderildi. Nereye ya da kime karşı, bilmiyorum, muhtemelen onlar da bilmiyordu. Bir daha da geri dönmediler.\n"+"... "+"Üzgünüm, kaptan. Başka bir zaman devam ederiz. Al bu şapkayı ve talimatları. Dün seni neşelendirmek için yaptım... Ama boşuna kendimi üzmüş oldum.";
            link.l1 = "Elbette, Alonso. Hediye için teşekkür ederim.";
            link.l1.go = "Alonso_Lvl_12_Gift";
        break;

        case "Alonso_Lvl_12_Gift":
            // Даём игроку шляпу
            GiveItem2Character(pchar, "hat10");
            SetAlchemyRecipeKnown("Hat10");

            DialogExit();
			AddDialogExitQuestFunction("LoyaltyPack_ThirdStage_DlgExit");
        break;

        // (Уровень 16) - Финальный
        case "Alonso_Lvl_16_Start":
			DelLandQuestMark(npchar);
			dialog.text = "Kaptan, sadece bildirmek istedim ki, artık tayfanız meyhanelerde ve genelevlerde krallar gibi ağırlanıyor. Sizin bayrağınız altında hizmet etmek artık bir anlam ifade ediyor!";
			link.l1 = "Teşekkürler, Alonso... Keşke ben de o kraliyet muamelesinden biraz görebilseydim.";
			link.l1.go = "Alonso_Lvl_16_1";
        break;

        case "Alonso_Lvl_16_1":
            dialog.text = "Yakında öğrenirsin. Karayipler, birkaç düzine kaptan arasında paylaşılan bir pasta gibi. Yakında sen de o masada yerini alacak ve payını kapacaksın.\n"+"Kim bilir? Belki de pastanın tamamını alan Karayipler efsanesi sen olacaksın.";
            link.l1 = "Hikayeni bitirecek misin? En son hapse atıldığın yerde kalmıştık.";
            link.l1.go = "Alonso_Lvl_16_2";
        break;

        case "Alonso_Lvl_16_2":
            dialog.text = "Ha! Büyük şapka hırsızlarının davası. Bir Moskof ve bir Portekizli, Flandre'de bir yerlerde küçücük bir hücrede. Karar bekliyorlar. Tabii ki, idam."+"Bizi önemli bir beyefendi kurtardı - meğerse Moskova elçisiymiş! Fadey'in eski dostuymuş. Yolundan geçiyormuş, başımıza gelenleri duymuş, özgürlüğümüzü satın almış!";
            link.l1 = "Fadey mi? O Fadey mi? Ve sen bunu gizli tuttun?!";
            link.l1.go = "Alonso_Lvl_16_3";
        break;

        case "Alonso_Lvl_16_3":
            dialog.text = "Evet. Yollarımız orada ayrıldı – o Moskova’sına döndü, ya Lehlerle savaşmaya ya da büyük bir iş çevirmeye. Ben de memlekette biraz daha oyalanıp durdum, işte şimdi buradayım.";
            link.l1 = "Etkileyici, Alonso. Bunca zamandır bana her şeyi anlattın ama kendinden hiç bahsetmedin. Senin gibi zeki birinin Engizisyon'u ağzından kaçırması da tuhaf.";
            link.l1.go = "Alonso_Lvl_16_4";
        break;

        case "Alonso_Lvl_16_4":
            dialog.text = "Ve sana en saf gerçeği söyledim, kaptan! Bana inanmıyorsan Fadey'e kendin sor. Onu Basse-Terre'de bulmak zor değil.";
            link.l1 = "Belki de yaparım. Peki hediyem nerede?";
            link.l1.go = "Alonso_Lvl_16_5";
        break;

        case "Alonso_Lvl_16_5":
            dialog.text = "Ha?";
            link.l1 = "Her hikayenin sonunda bana bir hediye verdin.";
            link.l1.go = "Alonso_Lvl_16_Escape";
        break;

        case "Alonso_Lvl_16_Escape":
			PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "Duydun mu? Çanlar çalıyor. İşe koyulma zamanı.";
            link.l1 = "Olduğun gibi kal, Alonso.";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("LoyaltyPack_FourthStage_DlgExit");
        break;
		
		// --> Эпилог
		case "SharlieEpilog_Alonso_1":
			dialog.text = "Floran hakkında mı? Ona zaten söyledim ki...";
			link.l1 = "Hayır dostum, konu tamamen farklı. Avrupa’ya gitmeye karar verdim. Süresiz olarak.";
			link.l1.go = "SharlieEpilog_Alonso_2";
		break;

		case "SharlieEpilog_Alonso_2":
			if (GetCompanionQuantity(pchar) <= 1) sStr = "gemimiz";
			else sStr = "gemilerimiz";
			dialog.text = "Sorun değil kaptan. Gemimiz sağlam, mürettebat deneyimli, sadece biraz erzak lazım...";
			link.l1 = "Başkasının gemisiyle gideceğim. Yolcu olarak. "+sStr+" liman idaresine park etmen ve mürettebatı dağıtman gerekecek. Ayrıca karar vermelisin: burada kalıp başka bir gemide görev almak mı, yoksa dost olarak benimle Fransa’ya gelmek mi?";
			link.l1.go = "SharlieEpilog_Alonso_3";
		break;

		case "SharlieEpilog_Alonso_3":
			dialog.text = "...";
			link.l1 = "Bu arada, tamamen alakasız bir şey: (fısıldayarak) Bordeaux’da birkaç hatun tanıyorum... Karayipler’de öyle büyücü gibisini bulamazsın. Senin gibi adamlara bayılıyorlar — hele bizim savaş hikâyelerini anlattığında...";
			link.l1.go = "SharlieEpilog_Alonso_4";
		break;

		case "SharlieEpilog_Alonso_4":
			dialog.text = "Söz konusu hatunlarsa... tamam, geliyorum. Hehe. Ama neden kendi gemimizle değil? Ve neden yolcu olarak? Adamlar biraz homurdanır belki ama seninle ister cennet, ister cehennem olsun, giderler.";
			link.l1 = "Buraya ilk geldiğimde kendimi denizci olarak hayal bile edemezdim. Ama şimdi başka bir hayat düşünemiyorum. Kaptan olmadığım bir hayatı kabullenebilir miyim... ve belki de yağmayı ve deniz hayatını geride bırakabilir miyim, bunu görmek istiyorum.";
			link.l1.go = "SharlieEpilog_Alonso_nothing";
			link.l2 = "Uzun hikâye. Meyhanede anlatırım — bir kadeh rom eşliğinde. Mürettebatı da davet et. Veda için güzel bir alem yapalım. Al bunu — bir aylık maaşlarını öde, tazminat niyetine.";
			link.l2.go = "SharlieEpilog_Alonso_salary";
		break;

		case "SharlieEpilog_Alonso_nothing":
			dialog.text = "Kaderden kaçış yok kaptan. Eğer ömrünün sonuna kadar kaptan olman yazıldıysa — öyle olur.";
			link.l1 = "Göreceğiz, "+npchar.name+", göreceğiz. Ama şimdilik — yapacak işlerimiz var. İki hafta içinde yola çıkıyoruz. Hangi gemiyle gideceğimizi asla tahmin edemezsin...";
			link.l1.go = "SharlieEpilog_Alonso_5";
		break;

		case "SharlieEpilog_Alonso_salary":
			dialog.text = "İşte şimdi oldu! Böylece onlara bu haberi vermek çok daha kolay olacak.";
			link.l1 = "Hangi gemiyle gideceğimizi asla tahmin edemezsin...";
			link.l1.go = "SharlieEpilog_Alonso_5";
			salary = GetSalaryForShip(PChar);
			AddMoneyToCharacter(pchar, - sti(npchar.quest.OfficerPrice));
		break;

		case "SharlieEpilog_Alonso_5":
			dialog.text = "Beni merakta bırakma kaptan.";
			link.l1 = "'"+GetShipName("Ulysse")+"' pinasasıyla.";
			link.l1.go = "SharlieEpilog_Alonso_6";
		break;

		case "SharlieEpilog_Alonso_6":
			dialog.text = "Olamaz... Yola çıktığımız gemiyle mi gidiyoruz? Kulaklarıma inanamıyorum...";
			link.l1 = "Aynen o, "+npchar.name+". Onu nasıl bulduğumu sonra anlatırım — meyhanede, bir rom eşliğinde. Ama şimdi yapmamız gereken şeyler var.";
			link.l1.go = "SharlieEpilog_Alonso_7";
		break;

		case "SharlieEpilog_Alonso_7":
			dialog.text = "Emredersiniz kaptan... Ahh... Adamlarla vedalaşmak zor olacak. Onlar benim için aile gibiler. Ama ne yapalım...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alonso";
			npchar.quest.SharlieEpilog_FarewellOfficers = true;
			AddDialogExitQuestFunction("SharlieEpilog_Alonso_exit");
		break;

		// эпилог <--
	}
} 