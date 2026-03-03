// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne istiyorsunuz? Sorunuzu sorun.","Dinliyorum, sorun nedir?"),"Bu ikinci kez sormaya çalışıyorsunuz...","Bu üçüncü kez tekrar sormaya çalışıyorsunuz...","Ne zaman bitecek bu?! Ben meşgul bir adamım, koloninin işleriyle uğraşıyorum ve sen hâlâ bir şeyler sormaya çalışıyorsun!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şimdi değil. Yeri ve zamanı değil."),"Doğru... Ama sonra, şimdi değil...","Soracağım... Ama biraz sonra...","Üzgünüm, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				link.l1 = "Monsieur, I have found a bandit's corpse in the jungle. He was killed by the Indians. There were earrings on his body; looks like they were brought here from Europe. Perhaps they belonged to one of the nobles in your town?";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца */
			//--> Sinistra, Травля крысы
			if (CheckAttribute(pchar, "questTemp.TK_Potopil"))
			{
				link.l1 = "Yüce Ekselansları, görev tamamlandı! Ne yazık ki, suçlu çatışmadan sağ çıkamadı; bu yüzden idam cezası uygulanamayacak.";
                link.l1.go = "TK_Potopil";
			}
			if (CheckAttribute(pchar, "questTemp.TK_Plen"))
			{
				link.l1 = "Majesteleri, görev tamamlandı! Mahkûm kaderini bekliyor, gemimin hücresinde.";
                link.l1.go = "TK_Plen";
			}
			//<-- Травля крысы
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "Vali General Philippe de Poincy'nin emriyle silahlı firkateyninizin komutasını devralmak üzere geldim.";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l1 = "Firkateyni filoma katmaya hazırım.";
                link.l1.go = "patria_2";
			}
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "message")
			{
				link.l1 = "Davetiniz üzerine geldim, Mösyö...";
                link.l1.go = "goldengirl";
			}
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "girl_prisoner")
			{
				link.l1 = "Bu talihsizlik oldu, Mösyö";
                link.l1.go = "goldengirl_10";
			}
			// andre39966 ===> В плену великого улова.
			if (CheckAttribute(pchar, "questTemp.VPVL_Magor_Dialogue"))
			{
				link.l1 = "Ekselansları, bu kıyılarda yakında gerçekleşecek yasa dışı ticaretle ilgili bazı bilgilere ulaştım. Bu meselenin dikkatinizi hak ettiğini düşünüyorum.";
				link.l1.go = "VPVL_Magor_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.VPVL_GovernorDialogueAvailable"))
			{
				link.l1 = "Ekselansları, konuştuğumuz o kaçakçı gemisiyle ilgili haberler almak için geldim.";
				link.l1.go = "VPVL_Magor_4";
			}
			//  <=== В плену великого улова.  
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Ne getirdiğine bir bakalım... İnanılmaz! Gerçekten inanılmaz, Charles! Bunlar eşimin küpeleri. Avrupa'dan ayrılıp kolonilere gelmeden önce ona vermiştim. Birkaç ay önce gizemli bir şekilde kayboldular. Çalındıklarını biliyordum!  Charles, doğrudan bana geldiğine ve benim için çok değerli olan bu eşyayı tüccarlara satmadığına çok memnun oldum. Bu iyiliğinin karşılığını ödeyeceğim. Duyduğuma göre bir gemi almayı düşünüyorsun? Denizciliğe atılmaya karar verdiğine göre, takımadamızın haritasına kesinlikle ihtiyacın olacak. Al, bu harita senin. Eminim işine yarayacaktır!";
			link.l1 = "Teşekkür ederim, Ekselansları!";
			link.l1.go = "Sharlie_junglejew_1";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "jewelry25", 1);
			GiveItem2Character(pchar, "map_normal");
			AddQuestRecord("SharlieE", "2");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(npchar);
			}
		break;
		
		//--> Sinistra, Травля крысы
		case "TK_Potopil":
			dialog.text = "Bu talihsiz bir durum, Charles, ama elimizdeki şartlarla yetinmek zorundayız. İşte ödülünüz: vergilerden sonra beş bin peso.";
			link.l1 = "St. Pierre'e ve size hizmet etmekten memnuniyet duyuyorum. Savaş zorlu geçti ama bundan bir nebze keyif aldım.";
			link.l1.go = "TK_Potopil_3";
			link.l2 = "Zorlu bir savaştı, Ekselansları. Gemim ciddi hasar aldı. Kayıplarım için bana tazminat vermeniz mümkün mü?";
			link.l2.go = "TK_Potopil_4";
			DeleteAttribute(pchar, "questTemp.TK_Potopil");
			AddCharacterExpToSkill(pchar, "Accuracy", 20);
			AddCharacterExpToSkill(pchar, "Cannons", 20);
			AddCharacterExpToSkill(pchar, "Grappling", 20);
			AddCharacterExpToSkill(pchar, "Defence", 20);
			
			CloseQuestHeader("TravlyaKrys");
		break;
		
		case "TK_Potopil_3":
			dialog.text = "Bravo, Charles! Şüphem yok ki saflarımızda çok yükseleceksin.";
			link.l1 = "Tekrar görüşene dek, Ekselansları.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		
		case "TK_Potopil_4":
			dialog.text = "Şunu söylemeliyim ki, bu talebin beni biraz şaşırttı Charles... Pekâlâ, iyi niyetimin bir göstergesi olarak şahsen iki bin peso daha vereceğim. Hoşça kal.";
			link.l1 = "Teşekkür ederim, Ekselansları.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 7000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
		break;
		
		case "TK_Plen":
			dialog.text = "Mükemmel, Charles! Başarınızın Malta’daki dostlarınıza hassas bir operasyonda yardımcı olacağını bilmek sizi memnun edecektir... İşte ödülünüz: vergilerden sonra sekiz bin peso.";
			link.l1 = "St. Pierre'e, Tarikat'a ve size şahsen hizmet etmekten memnuniyet duyuyorum. Savaş zorlu geçti ama bunda bir nebze tatmin buldum.";
			link.l1.go = "TK_Plen_3";
			link.l2 = "Zorlu bir savaş oldu, Ekselansları. Gemim ciddi hasar aldı. Kayıplarım için tazminat talep edebilir miyim?";
			link.l2.go = "TK_Plen_4";
			AddCharacterExpToSkill(pchar, "Accuracy", 20);
			AddCharacterExpToSkill(pchar, "Cannons", 20);
			AddCharacterExpToSkill(pchar, "Grappling", 20);
			AddCharacterExpToSkill(pchar, "Defence", 20);
			CloseQuestHeader("TravlyaKrys");
			DeleteAttribute(pchar, "questTemp.TK_Plen");
			sld = CharacterFromID("TK_Heiter2");
			RemovePassenger(pchar, sld);
			sld.lifeday = 0;
		break;
		
		case "TK_Plen_3":
			dialog.text = "Bravo, Charles! Eminim çok yol kat edeceksin.";
			link.l1 = "Tekrar görüşene dek, Ekselansları";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 8000);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		
		case "TK_Plen_4":
			dialog.text = "Bunu hak ettiğini düşünüyorum. İyi niyetimin bir göstergesi olarak benden şahsen iki bin altını daha al. Teşekkür ederim, dostum.";
			link.l1 = "Teşekkür ederim, Ekselansları.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 10000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
		break;
		//<-- Травля крысы
		
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "Gemi hazır, fakat filonuzda onun için boş bir yer yok. Kaptan, filonuzu küçültüp geri dönün, o zaman hemen size fırkateyni teslim edeceğim.";
				link.l1 = "Pekala.";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "Evet, elbette, gemi sefere hazır. Kaptanı durumun farkında ve tüm emirlerinizi yerine getirecek.";
				link.l1 = "O halde yola çıkıyoruz. Hoşça kalın, Ekselansları.";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "Mükemmel. Yeni geminizi karşılamaya hazırlanın. Kaptanı bilgilendirildi ve tüm emirlerinizi yerine getirecek.";
			link.l1 = "O halde yola çıkıyoruz. Hoşça kalın, Ekselansları.";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateMrt(); // присоединяем фрегат
		break;
		
		// Jason Дороже золота
		case "goldengirl":
			dialog.text = "Kaptan Charles de Maure, sonunda! Sizi sabırsızlıkla bekliyordum! Lütfen, buyurun, bana katılın.";
			link.l1 = "Sana da iyi günler, Ekselansları. Bu kadar nazik olmanızın her zaman bir sebebi vardır. Bu sefer ne oldu? Korsanlar mı, İspanyollar mı, yoksa Kızılderili yamyamlar mı?";
			link.l1.go = "goldengirl_1";
		break;
		
		case "goldengirl_1":
			dialog.text = "İronikleşme hemen, Kaptan. Sürekli başımızın belaya girmesi benim suçum değil, seninle benim. Ama lütfen, endişelenme, bu sefer silahlar patlamayacak... muhtemelen.";
			link.l1 = "İlgimi çektiniz, devam edin. Size nasıl yardımcı olabilirim?";
			link.l1.go = "goldengirl_2";
		break;
		
		case "goldengirl_2":
			dialog.text = "Madame Botot'nun seçkin işletmesini duydunuz mu? Kuşatma sırasında... genelevimiz kül oldu. Bir gün, belli bir hanımefendi yeniden inşa etmeye gönüllü oldu.";
			link.l1 = "Bir genelevde yangın çıkmış ve ben orada yokum? Bu arada, o gün İspanyollar tarafından da vuruldum.";
			link.l1.go = "goldengirl_3";
		break;
		
		case "goldengirl_3":
			dialog.text = "Lanet olsun Charles, bugün sana ne oldu? Esprilerin hiç yeri değil! Devlet meselesi olmasa da, bu konu benim için, şahsen, çok önemli! Yardımına ihtiyacım var! Allah aşkına, kendine gel ve beni dinle!";
			link.l1 = "Affedersiniz, Ekselansları. Sadece büyük bir rahatlama hissediyorum, hepsi bu. Açıkçası, bu bitmek bilmeyen savaşlardan ve çatışmalardan yoruldum. Sizi beni yeni bir şiddet döngüsüne sürükleyeceksiniz diye bekliyordum. Lütfen devam edin. Bu Madame Botot'u hiç duymadım.";
			link.l1.go = "goldengirl_4";
		break;
		
		case "goldengirl_4":
			dialog.text = "Evet, bu saygıdeğer hanımefendi mekanı bambaşka bir seviyeye taşıdı. Artık burası eskisi gibi bir fare deliği değil, yüksek ve soylu bir topluluğun buluşma yeri. Seçkin zevkler, pahalı şaraplar ve sınırsız kumar burada. Her şeyi kendiniz göreceksiniz!";
			link.l1 = "Ekselansları, ben tutucu biri değilim ve anlattıklarınız oldukça renkliydi, fakat bunu bana neden anlatıyorsunuz?";
			link.l1.go = "goldengirl_5";
		break;
		
		case "goldengirl_5":
			dialog.text = "Çünkü listedesin, başka neden olabilir ki?! Bak, Markiz için kendimi suçlu hissediyorum ve sana yarınki partisinde onu tanıştıracağıma söz verdim. Juliana bunu sık yapmaz, bu yüzden lütfen bize katılma nezaketini göster. Bu sefer kavga yok, silah yok, kovalamaca yok, söz veriyorum. Her şey nazikçe ve asilce olacak: şarap, güzel kadınlar, iskambil ve diğer soylu zevkler.";
			link.l1 = "Kartlar ve kadınlar. Uzun zaman oldu, başka bir hayatta. Yine de seni hâlâ anlamıyorum. Neden ben?";
			link.l1.go = "goldengirl_6";
		break;
		
		case "goldengirl_6":
			dialog.text = "Sağır mısınız? Juliana Botot, o... parlak ve ünlü simaları toplar. Partilerini özel ve canlı kılan da budur. Siz kendinize epey bir isim yaptınız, Markiz uzun zamandır sizi misafiri olarak görmek istiyordu. Benim hatam ona bir fırsat verdi, ve eğer beni tekrar kabul etmeyi reddederse, bu fırsatı değerlendirmeyeceğim. Sizi ona götürmezsem alacağım tek şey bu!";
			link.l1 = "Excellency, siz yakışıklı bir dul ve bir valisiniz... Neden bir saraylı kadının fikrine önem veresiniz ki? Aslında onlar sizin ilginizi aramalı, tam tersi değil.";
			link.l1.go = "goldengirl_7";
		break;
		
		case "goldengirl_7":
			dialog.text = "Marquise Botot, Kont Henry de Levi-Vantadur’un koruması altında – ki kendisi Majestelerinin lütfuyla Yeni Fransa’nın Kuzey Amerika’daki eyaletlerinin başıdır. Bana güven, Charles, burada kimse onunla ters düşmek istemez.";
			link.l1 = "Az kalsın kandırıyordun beni – bunun sadece arzu ve aşk meselesi olduğunu sanmıştım. Şimdi görüyorum ki işin içinde baştan beri siyaset varmış. Önemsiz ama beklenen bir durum. Pekâlâ, sana yardım edeceğim. Gençlik günlerime sadece bir gece olsun dönmek güzel olacak.";
			link.l1.go = "goldengirl_8";
		break;
		
		case "goldengirl_8":
			dialog.text = "Kaptan, tecrübeli bir adamsınız, bunda şüphe yok, ama yaşlı bir adam rolü yapmaya kalkmayın. Mesele sadece siyaset değil. Juliana'nın varlığını önemsiyorum ve yardımınız için minnettarım. Bu benim için gerçekten kişisel bir mesele. Yarın gün batımından sonra Marquise Botot'nun evine gelin. Size söz veriyorum, geceyi siyaset bozmayacak.";
			link.l1 = "Şarap, iskambil, kadınlar. Eski güzel günler gibi. Elveda, Ekselansları!";
			link.l1.go = "goldengirl_9";
		break;
		
		case "goldengirl_9":
			DialogExit();
			bDisableFastReload = true;//закрыть переход
			pchar.quest.GoldenGirl_bronca.win_condition.l1 = "location";
			pchar.quest.GoldenGirl_bronca.win_condition.l1.location = "FortFrance_town";
			pchar.quest.GoldenGirl_bronca.function = "GoldenGirl_GirlAngry";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("GoldenGirl_TimeOver", 0, 0, 2, false); // таймер до завтрашней полуночи
			SetFunctionTimerCondition("GoldenGirl_BrothelDoor", 0, 0, 1, false); // таймер на закрытие дверей борделя
			pchar.quest.GoldenGirl_eventstart.win_condition.l1 = "Timer";
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.hour  = 21.00;
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l2 = "location";
			pchar.quest.GoldenGirl_eventstart.win_condition.l2.location = "FortFrance_SecBrRoom"; // возможно закрыть бордель и вход только через боковую комнату
			pchar.quest.GoldenGirl_eventstart.function = "GoldenGirl_Party"; // таймер на начало вечеринки
			pchar.questTemp.GoldenGirl = "brothel";
			AddQuestRecord("GoldenGirl", "2");
		break;
		
		case "goldengirl_10":
			dialog.text = "Charles, ne oldu, perişan görünüyorsun!";
			link.l1 = "Angerran, kahrolası Chievous, Ekselansları. Dün gece fırkateynimi çaldı. Ödül mürettebatımı öldürdü ve sisin içinde yelken açtı.";
			link.l1.go = "goldengirl_11";
		break;
		
		case "goldengirl_11":
			dialog.text = "Bu hoş olmayan bir gelişme, anlıyorum, ama bana güvenin - böyle bir sonuç oldukça tatmin edici. Ne gemilere ne de adamlara acil ihtiyacınız var, öte yandan de Levi Vantadour yakın zamanda gerçekleşen bir düellonun ardındaki gerçeği gizlemek için hatırı sayılır bir meblağ ödeyecek. Ya da bunu ücretsiz gizlememizdeki rolümüzü aklında tutacak, ki bu da oldukça değerli. De Chievous iki kez dürüst olmayan işler yaptı, ama artık çok uzakta, biz ise ona karşı hâlâ iyi kozlara sahibiz.";
			link.l1 = "Üç kez, Ekselansları. Angerran, kart oyununda hile yaptığını itiraf etti. Ama eğer kastettiğiniz buysa, bana parayla borcunu ödemeyecek. Sınırı aştı. Bu sabah o gemide biri vardı... o bana çok kıymetli! O alçağın ona zarar vermesine asla izin vermem! Duydun mu Jacques, asla izin vermem!";
			link.l1.go = "goldengirl_12";
		break;
		
		case "goldengirl_12":
			dialog.text = "Bence kimi kastettiğini biliyorum - seni bir keresinde... bir kızla gördüğümü hatırlıyorum, erkek gibi giyinmişti ve bir korsan gibi silahlanmıştı. Charles, aptallık etme! Şanslıydın, büyük bir beladan kurtuldun ve şimdi ne yapıyorsun, kendini tekrar belanın içine mi atmaya çalışıyorsun? Bırak gitsin. De Chievous kaçıyor - Tanrı'ya şükür! Ve o 'silah arkadaşın' için - dostunun tavsiyesini dinle - Julianna'yı gör ve bütün bunları unut.";
			link.l1 = "Bu söz konusu bile olamaz, Ekselansları. Bazı şeyler sizin anlayışınızın ötesinde, tamam mı? Şimdi bana o alçak hakkında bildiğiniz her şeyi anlatın. Saint Pierre'den sonra nereye gitmiş olabilir? Ve beni bir daha vazgeçirmeye çalışmayın – Hollanda Şirketi'yle de kapıştım, korsan baronlarıyla da, genel valilerle de, hatta Kutsal Engizisyon'la bile! Kolay kolay korkacak biri değilim. Onu geri alacağım, bedeli ne olursa olsun!";
			link.l1.go = "goldengirl_13";
		break;
		
		case "goldengirl_13":
			dialog.text = "Charles, have you ever given any thought to the question of who appoints governor-generals? This is an entirely different world! You have barely scratched its surface; it is beyond your understanding, you are like a child in a gunpowder store. And you are asking me to hand you a lit candle. As for governor-generals: de Poincy himself never crosses the count, neither in matters of coin nor in matters of politics. Vice King, the term so popular among the commoners, would suit Henri de Lévis Ventadour just fine.";
			link.l1 = "Ve işte buradayım, onun tek erkek varisini öldürmeyi planlıyorum. Burada neyi riske attığımın farkındayım. Şimdi, bana sadece şunu söyle: bana yardımcı olabilecek bildiğin herhangi bir faydalı şey var mı?";
			link.l1.go = "goldengirl_14";
		break;
		
		case "goldengirl_14":
			dialog.text = "On any other day, I would take you reaching for your pistol as the end of our friendship, Charles. But I understand your current state of mind. That is why I am willing to let this go. I know nothing useful to you; the frigate sailed west early this morning. You should pay a visit to the Marquise... Wait, not like that! Julianna knows a great deal about your enemy, and she was personally... acquainted with his father for some time. Ask her. Unlike me, she won't try to stop you.";
			link.l1 = "Planımız bu. Görüşmek üzere, Ekselansları. Zamanınızı ayırdığınız için teşekkür ederim.";
			link.l1.go = "goldengirl_15";
		break;
		
		case "goldengirl_15":
			DialogExit();
			LocatorReloadEnterDisable("FortFrance_town", "reload9_back", false); 
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_58";
			LAi_SetOwnerType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			pchar.questTemp.GoldenGirl = "find_girl";
		break;
		
		// В плену великого улова, andre39966
		case "VPVL_Magor_1":
			dialog.text = "Kaçak mallar mı diyorsunuz? Hmm... son derece ilginç. Lütfen, keşfinizin ayrıntılarını bana anlatın.";
			link.l1 = "Üç gün önce, kaçak yük taşıyan bir geminin Le Marin Körfezi'ne demirlemesi bekleniyordu. Gemi buluşma yerine ulaşamadı, fakat elimde sağlam nedenler var ki, yakında limana varacak. Adamlarınız bu haydutlara geldiklerinde layıkıyla bir karşılama hazırlayabilirler mi, Ekselansları?";
			link.l1.go = "VPVL_Magor_2";
			pchar.questTemp.VPVL_DontSpawnSmugglersShip = true; 
			DelLandQuestMark(npchar);
		break;

		case "VPVL_Magor_2":
			dialog.text = "İsimsiz bir gemi, adı bilinmeyen bir yük taşıyor... Ve siz, Majestelerinin kuvvetlerini böylesine belirsiz bir bilgiye dayanarak göndermemi mi bekliyorsunuz?";
			link.l1 = "Ekselansları, ayrıntıların az olduğunu kabul ediyorum. Ancak lütfen, bu bilgilerin elime nasıl geçtiğini size anlatmama izin verin. (Ara sahne)";
			link.l1.go = "VPVL_Magor_3";
		break;

		case "VPVL_Magor_3":
			dialog.text = "Pekâlâ, zekânızı sınayacağız. Eğer gerçekten kaçak mal taşıyan bir gemi Le Marin kıyılarında demir atarsa, Taç'a yaptığınız hizmet karşılığında cömertçe ödüllendirileceksiniz. Üç gün sonra bana geri dönün. O zamana kadar, belirsizliğin sisi dağılmış olur.";
			link.l1 = "Mükemmel. O halde üç gün sonra görüşürüz.";
			link.l1.go = "VPVL_Delete_Spawn_Ship";
			AddDialogExitQuest("VPVL_SetGovernorDialogueFlag");
			AddQuestRecord("VPVL", "6");
		break;

		case "VPVL_Magor_4":
			dialog.text = "Ah, Kaptan! Sizi tekrar ağırlamak büyük bir zevk. Verdiğiniz istihbarat gerçekten çok değerliydi. Adamlarım gemiyi tam belirttiğiniz yerde yakaladı. Buyurun—yüz elli İspanyol dublonu, yeni basılmış ve kesenizi ağırlaştıracak kadar değerli. Minnettarlığımı kabul edin ve bunları alın.";
			link.l1 = "Alçakgönüllü teşekkürlerimi sunarım, Ekselansları. Küçük bir istihbarat parçamın Taç'ın çıkarlarına hizmet etmesi benim için büyük bir şans. Yine bir fırsat doğarsa, biliniz ki kılıcım ve keskin gözüm emrinizde olmaya devam edecektir.";
			link.l1.go = "VPVL_Delete_Flag";
			AddItems(PChar, "gold_dublon", 150);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			DelLandQuestMark(npchar);
		break;

		case "VPVL_Delete_Flag":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.VPVL_GovernorDialogueAvailable");
			DeleteAttribute(pchar, "questTemp.VPVL_DontSpawnSmugglersShip");
		break;

		case "VPVL_Delete_Spawn_Ship":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
			AddDialogExitQuest("VPVL_KillCapitanOfSmuggler");
		break;
		// <=== В плену великого улова
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
