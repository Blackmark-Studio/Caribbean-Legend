// диалоги НПС по квесту 'В поисках Стража Истины'
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
			dialog.text = "Sana nasıl yardımcı olabilirim?";
			link.l1 = "Üzgünüm, önemli bir şey değil.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// пленный испанец
		case "spa_prisoner":
			PlaySound("Voice\English\Ransack_1.wav");
			dialog.text = "Ne istiyorsun? Yine mi sorgu? Vete al diablo!";
			link.l1 = "Beyefendi, adınız nedir?";
			link.l1.go = "spa_prisoner_1";			
		break;
		
		case "spa_prisoner_1":
			dialog.text = "Adamın adını asacaksan ya da vuracaksan sana ne önemi var? Bastardo! Sonunda senin eline düşecek kadar dikkatsiz davrandım işte...";
			link.l1 = "Beyefendi, kendinizi tanıtın. İsminizi bilmeden sizinle konuşamam.";
			link.l1.go = "spa_prisoner_2";			
		break;
		
		case "spa_prisoner_2":
			dialog.text = "Don "+GetFullName(npchar)+". Oldu mu şimdi, memnun musun? Peki, kiminle konuşma şerefine nail oldum?";
			link.l1 = "Benim adım "+GetFullName(pchar)+" . Daha önce hiç benden bahsedildiğini duydun mu?";
			link.l1.go = "spa_prisoner_3";			
		break;
		
		case "spa_prisoner_3":
			dialog.text = "Hayır, carajo! Batı Hint Adaları'ndaki her serseriyi tanıyormuş gibi mi görünüyorum ben...";
			link.l1 = "Yeter. Bunu hakaret etmeden ve centilmen gibi davranarak halledelim. Kaderin bana anlatacaklarına bağlı olacak. Eğer bana ilginç bir şey söylersen, seni gözetimime almak için dilekçe vereceğim. Böylece şu an seni bekleyen kurşundan ya da ilmeğe gitmekten kurtulabilirsin.";
			link.l1.go = "spa_prisoner_4";			
		break;
		
		case "spa_prisoner_4":
			dialog.text = "Dios mio, bu teklife hayır diyemem. Ne öğrenmek istersiniz, señor?";
			link.l1 = "St. Pierre'ye bu kadar büyük bir saldırıyı kim düzenledi ve neden?";
			link.l1.go = "spa_prisoner_5";			
		break;
		
		case "spa_prisoner_5":
			dialog.text = "Providence Adası'nın garnizon komutanı Baron Ramon de Mendoza y Riba. Kasabayı yağmalamak ve bulabildiğimiz tüm değerli eşyaları ele geçirmek için bir filo gönderdi.";
			link.l1 = "Saldırı sırasında derhal yerine getirmen gereken görev neydi? Özellikle, sana verilen emirler neydi?";
			link.l1.go = "spa_prisoner_6";			
		break;
		
		case "spa_prisoner_6":
			dialog.text = "Ben deniz piyade taburunun komutanıyım. Emrimiz, kaleyi ele geçirip toplarını kontrol altına alarak, çıkarma botlarımız kasabaya yaklaşırken ateş açmalarını engellemekti. Sonrasında adamlarım St. Pierre’e yapılan saldırıya katıldılar.";
			link.l1 = "Şehirde bulunan değerli eşyalar hakkında bilgilendirildiniz mi? Miktarları ve kaliteleri hakkında?";
			link.l1.go = "spa_prisoner_7";			
		break;
		
		case "spa_prisoner_7":
			dialog.text = "Kesin bir miktar bilgimiz yoktu, ama Baron de Mendoza y Riba bize kalenin altında gümüş saklandığını ve liman depolarında savaş için hayati öneme sahip stratejik hammaddeler bulunduğunu söyledi: demir ağacı ve gemi ipeği.";
			link.l1 = "O değerli eşyaları buldun mu?";
			link.l1.go = "spa_prisoner_8";			
		break;
		
		case "spa_prisoner_8":
			dialog.text = "Hayır. Hiçbirini bulamadık. Depolar sıradan sömürge mallarıyla doluydu, kalenin altında ise barut, silah ve kurşun vardı. Ama daha detaylı bir arama yapacak vaktimiz yoktu... Fransız takviyeleri gürültüyle geldi ve savaşmak zorunda kaldık.";
			link.l1 = "Değerli eşyaları bulamadığına hiç garip gelmedi mi?";
			link.l1.go = "spa_prisoner_9";			
		break;
		
		case "spa_prisoner_9":
			dialog.text = "Elbette yaptım, ama genelde emirleri sorgulamam.";
			link.l1 = "Şimdi sana anlatacaklarımı iyi dinle. Fort St. Pierre’de hiç gümüş olmadı, o depolarda da demir ağacı ya da ipek saklanmadı. İyi düşün, señor, cevap vermeden önce. Çünkü cevabın hoşuma gitmezse, arkamı döner giderim ve seni kaderinle baş başa bırakırım... hem de acı bir kaderle.";
			link.l1.go = "spa_prisoner_10";			
		break;
		
		case "spa_prisoner_10":
			dialog.text = "Dinliyorum.";
			link.l1 = "Senin baskınının tek amacının basit bir soygun olduğuna inanmıyorum. St. Pierre, tüm bir filoyu ve birinci sınıf bir savaş gemisini buraya göndermek için fazla önemsiz ve nispeten yoksul bir koloni. Eminim ki sen, komutanın ya da başka biri ek talimatlar ya da emirler almışsınızdır. Sana ne söylediler? Cevap vermeden önce iyi düşün...";
			link.l1.go = "spa_prisoner_11";			
		break;
		
		case "spa_prisoner_11":
			dialog.text = "";
			link.l1 = "Sessiz kalacaksın yani? Peki. Biraz düşün, ben beklerim.";
			link.l1.go = "spa_prisoner_12";			
		break;
		
		case "spa_prisoner_12":
			dialog.text = "Señor, hayatım cevabıma mı bağlı?";
			link.l1 = "Doğru.";
			link.l1.go = "spa_prisoner_13";			
		break;
		
		case "spa_prisoner_13":
			dialog.text = "Bir şeyim var... Ama bana yemin etmelisin ki, buradan çıkaracak ve beni fidyeyle İspanya'ya geri göndereceksin.";
			link.l1 = "Bana ilgimi çekecek bir şey söylersen, Kutsal Haç üzerine yemin ederim ki seni gemime fidye için aldırır, idamdan kurtarırım.";
			link.l1.go = "spa_prisoner_14";			
		break;
		
		case "spa_prisoner_14":
			dialog.text = "Pekâlâ. Don Diego de Montoya, deniz piyadeleri taburumuza en büyük gizlilik ve aciliyetle, yetkililerin koruması altındaki St. Pierre'de bir yerde bulunan Miguel Dichoso adında bir adamı bulup yakalamamız gerektiğini söyledi.";
			link.l1 = "Devam et. Diego de Montoya kim?";
			link.l1.go = "spa_prisoner_15";			
		break;
		
		case "spa_prisoner_15":
			dialog.text = "Filonun komutanı olan subay. Sizin... çarpıcı gelişinizden hemen sonra kaçtı.";
			link.l1 = "Kim bu Don Diego?";
			link.l1.go = "spa_prisoner_16";			
		break;
		
		case "spa_prisoner_16":
			dialog.text = "Tek bildiğim, Barones de Mendosa y Riba'nın yetkili temsilcisi olduğu; onun sağ kolu ve kritik işler için görevlendirdiği adamı.";
			link.l1 = "İlginç... Peki ya Miguel Dichoso kim, bütün bu felaketin yakalamak için düzenlendiği adam? Kötü biri olmalı, değil mi?";
			link.l1.go = "spa_prisoner_17";			
		break;
		
		case "spa_prisoner_17":
			dialog.text = "Yeminini hatırlıyor musun, señor?";
			link.l1 = "Evet. Ve sana temin ederim ki hikayeni anlatmaya devam edersen, seni kilit bir tanık olarak gemime götüreceğim ve sonra... bir şekilde seni bir İspanyol yerleşimine ulaştırmanın yolunu bulurum. Ama önce bildiğin her şeyi bana anlatacaksın.";
			link.l1.go = "spa_prisoner_18";			
		break;
		
		case "spa_prisoner_18":
			dialog.text = "Miguel Dichoso, baronun eski silah arkadaşıdır, gerçi bazıları Miguel'in ona ihanet ettiğini söylüyor. Señor de Mendoza y Riba onu canlı istiyor, bu yüzden hiçbir koşulda Dichoso'yu öldürmememiz emredildi.";
			link.l1 = "Dichoso da mı bir İspanyol?";
			link.l1.go = "spa_prisoner_19";			
		break;
		
		case "spa_prisoner_19":
			dialog.text = "Evet. Don Diego de Montoya bize yaklaşık bir tarif verdi ve Dichoso'ya benzeyen herhangi bir adamın doğrudan ona teslim edilmesini emretti. Ama sizin karşı saldırınızdan önce çok az vaktimiz olduğu için arama fırsatımız hiç olmadı.";
			link.l1 = "Dichoso'yu şahsen tanır mıydın?";
			link.l1.go = "spa_prisoner_20";			
		break;
		
		case "spa_prisoner_20":
			dialog.text = "Hayır, sadece ününü duydum. Adamı daha önce hiç görmedim. Bazı meslektaşlarım onu şahsen tanıyordu. Hepsi öldü.";
			link.l1 = "Dichoso, Don Mendoza'ya ne kadar büyük bir ihanet etti ki, peşine koca bir filo gönderdi?";
			link.l1.go = "spa_prisoner_21";			
		break;
		
		case "spa_prisoner_21":
			dialog.text = "I will tell you. The baron only recently arrived in the Caribbean from Spain. His orders were to ensure the safety of the Spanish Treasure Fleet convoys, but instead he looked inland... searching for Indian gold. His head was turned by rumours of hidden treasure. He decided that an ancient Maya city exists somewhere deep in Yucatan's jungles - Tayasal, the legendary city of gold\nThe baron sent several expeditions to find the city, but all of them were utterly vanquished in the wild selva. No doubt each and every one of them was slaughtered by the martial Itza people who live there\nEventually, Inquisitor Vincento had enough of Don Mendosa's fantasies and the pointless deaths of good soldiers. The inquisitor informed Madrid about the situation. The viceroy forbade Don Mendosa to search for the mythical city and ordered him to focus on his duties. That's when Miguel Dichoso showed up\nHe convinced the baron to organise another expedition, which, surprisingly, was a success. They found ruins of an ancient city and a pile of gold encrusted with jewels. But on their return, they were attacked by the Mosquito tribe\nAll except Miguel perished; the Indian darts are dipped in some local poison, even a small scratch leads to certain, agonising death in a few days. Dichoso returned to Providence with what treasure he could carry\nCarajo! The baron was unspeakably happy, he sent urgent letters to Madrid and to Father Vincento in Santiago; no doubt he wanted to rub his success in the Reverend Father's face. Then a frigate was prepared to deliver the treasure back to Spain. Dichoso volunteered to escort it.";
			link.l1 = "Dur tahmin edeyim. Altını teslim etmedi, değil mi?";
			link.l1.go = "spa_prisoner_22";			
		break;
		
		case "spa_prisoner_22":
			dialog.text = "Doğru, señor! Fırkateyn, tüm yükü ve mürettebatıyla birlikte, Dichoso dahil, iz bırakmadan kayboldu. Baron öfke içindeydi. Bir kez daha Escorial önünde küçük düşürüldü, bu da Peder Vincento'nun büyük memnuniyetine yol açtı. Şimdi Don Mendosa, incinen gururunu, kaybolan hazinesini ve Miguel Dichoso'yu geri kazanma takıntısıyla yanıp tutuşan bir adam.";
			link.l1 = "Fırkateynin bir fırtınaya yakalanıp batmış ya da korsanlar tarafından ele geçirilmiş olması mümkün değil mi?";
			link.l1.go = "spa_prisoner_23";			
		break;
		
		case "spa_prisoner_23":
			dialog.text = "Baron o anın sıcaklığında Dichoso'nun ona ihanet ettiğine yemin etti. Ayrıntıları bilmiyorum. Birkaç hafta sonra Don Diego de Montoya, Miguel Dichoso'nun St. Pierre'de olabileceğine dair yeni bilgilerle geldi.";
			link.l1 = "Hm. İlginç. Yine o Hint hazineleri. Her şey tuhaf bir şekilde onlara bağlı görünüyor... Yani, Dichoso'yu bulamadın mı?";
			link.l1.go = "spa_prisoner_24";			
		break;
		
		case "spa_prisoner_24":
			dialog.text = "Hayır. Ve açıkçası, buraya hiç gelmiş olsaydı bile şaşırırdım. Baron, Dichoso'yu yakalama fikrine öyle takıntılı ki, en uçuk hayallere bile inanır.";
			link.l1 = "Söyle bana, "+npchar.name+", Don Mendosa bu... şey... Tayasal şehri hakkında nasıl bilgi aldı? Kafasından uydurmadı ya? Bir kanıt ya da başka bir şey var mıydı?";
			link.l1.go = "spa_prisoner_25";			
		break;
		
		case "spa_prisoner_25":
			dialog.text = " Tayasal'ın ve altın şehrinin varlığını ilk duyan kişi Peder Vincento'ydu. Nereden öğrendiğini ise hiç bilmiyorum... ";
			link.l1 = "Bu ilginç bir gelişme. Peder Vincento Tayasal'ın varlığı teorisini kendi başına ortaya attı, İspanya'ya bizzat haber verdi ve baronun işine çomak sokmaya başladı...";
			link.l1.go = "spa_prisoner_26";			
		break;
		
		case "spa_prisoner_26":
			dialog.text = "Sen de bir Katolik olarak, Kutsal Mahkeme'nin bu muhterem rahiplerinin nasıl işlediğini bilirsin... Madrid'e boşuna haber vermedi. Bir hesabı var ama baronun gelişi belli ki planlarında yoktu. Neyse, bu konuda daha fazlasını bilmiyorum. Engizisyon'la uğraşmak hiç istemedim.";
			link.l1 = "Pekala. Bana oldukça ilginç bilgiler verdin, "+npchar.name+", ve yeminime sadık kalarak, seni buradan çıkarıyorum. Sonra tekrar geri döneceğim, ama şimdilik... bana anlattıklarını biraz düşünmem gerek...";
			link.l1.go = "spa_prisoner_27";			
		break;
		
		case "spa_prisoner_27":
			DialogExit();
			pchar.questTemp.Guardoftruth = "think";
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto3", "GuardOT_MCthink", -1);
		break;
		
		case "spa_prisoner_28":
			PlaySound("Voice\English\Ransack_2.wav");
			dialog.text = "Señor? Sözünüzü tutacak mısınız?";
			link.l1 = "Ben her zaman sözümü tutarım. Bugün senin şanslı günün, "+npchar.name+". Benimle birlikte Küba'daki Santiago'ya geliyorsun. Planımı oraya vardığımızda daha ayrıntılı anlatırım. Ama şimdilik, gemime hoş geldin. Limana kadar sana eşlik edecekler ve seni gemime getirecekler.";
			link.l1.go = "spa_prisoner_29";			
		break;
		
		case "spa_prisoner_29":
			dialog.text = "Teşekkür ederim, kaptan. Sözünün eri bir centilmen olmanıza sevindim.";
			link.l1 = "Teşekkürünü sonra edersin. Misafirim olacaksın, ama gözetim altında. Yanlış anlama, sana hâlâ ihtiyacım var.";
			link.l1.go = "spa_prisoner_30";			
		break;
		
		case "spa_prisoner_30":
			dialog.text = "Anladım, señor. Bir İspanyol subayı olarak size söz veriyorum, kaçmaya hiçbir şekilde teşebbüs etmeyeceğim.";
			link.l1 = "Tedbiri elden bırakmayanı Tanrı korur. Gemide görüşürüz.";
			link.l1.go = "spa_prisoner_31";			
		break;
		
		case "spa_prisoner_31":
			DialogExit();
			pchar.questTemp.Guardoftruth = "cuba";
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.quest.GuardOT_exitbase.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_exitbase.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_exitbase.function = "GuardOT_ExitFrombase";
			AddQuestRecord("Guardoftruth", "4");
		break;
		
		case "spa_prisoner_32":
			PlaySound("Voice\English\Serve_senior.wav");
			dialog.text = "Kaptan, burada Küba'da ne yapmayı düşünüyorsunuz? Beni burada bırakacak mısınız? Buna inanmak bile istemiyorum...";
			link.l1 = "Tam olarak doğru, seni kendi insanlarına geri götürmek için buradayım. Fakat buraya gelişimin sebebi bundan biraz daha karmaşık. Ama bu artık seni ilgilendirmiyor. Seni hemen şimdi fidye istemeden serbest bırakacağım, ama bana iki şeye yemin etmeni şart koşuyorum.";
			link.l1.go = "spa_prisoner_33";			
		break;
		
		case "spa_prisoner_33":
			dialog.text = "Onlar ne?";
			link.l1 = "İlki şu: Sana mühürlü bir mektup vereceğim. O mektubu bizzat Santiago Engizitörü Peder Vincento'ya teslim edeceksin. Eğer mektubun kimden geldiğini ve nasıl aldığını sorarsa, ona gerçeği söyle...";
			link.l1.go = "spa_prisoner_34";			
		break;
		
		case "spa_prisoner_34":
			dialog.text = "";
			link.l1 = "İkincisi, beni bulmaya ya da gemime saldırmaya yönelik hiçbir girişime en az bir hafta boyunca yardım etmeyecek ya da destek olmayacaksın. Anlaştık mı?";
			link.l1.go = "spa_prisoner_35";			
		break;
		
		case "spa_prisoner_35":
			dialog.text = "Hepsi bu mu?";
			link.l1 = "Evet, hepsi bu. Şartlarımı yerine getir, gidebilirsin.";
			link.l1.go = "spa_prisoner_36";			
		break;
		
		case "spa_prisoner_36":
			dialog.text = "Sana yemin ederim, señor, mektubu bizzat Peder Vincento'ya teslim edeceğim ve Santiago garnizonunun sana ya da gemine saldırmasına yol açabilecek hiçbir harekette bulunmayacağım. İçin rahat olsun, sözümü tutacağım. Ben bir İspanyolum ve güçlü, asil rakiplere saygı duyarım.";
			link.l1 = "Pekâlâ, Don "+GetFullName(npchar)+", Yeminini kabul ediyorum ve seni hemen serbest bırakıyorum. Al, bu mektubu Engizitör'e götür. Artık özgürsün.";
			link.l1.go = "spa_prisoner_37";			
		break;
		
		case "spa_prisoner_37":
			Log_Info("You've given the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "Elveda, señor. Umarım bir daha savaş meydanında karşılaşmayız. Bu beni gerçekten üzerdi.";
			link.l1 = "Elveda...";
			link.l1.go = "spa_prisoner_38";			
		break;
		
		case "spa_prisoner_38":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Guardoftruth", "5");
			pchar.quest.GuardOT_mayak.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_mayak.win_condition.l1.date.hour  = sti(GetTime()-(rand(4)));
			pchar.quest.GuardOT_mayak.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l2 = "location";
			pchar.quest.GuardOT_mayak.win_condition.l2.location = "mayak9";
			pchar.quest.GuardOT_mayak.function = "GuardOT_CreateVinsentoAgent";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "spa_prisoner_39":
			dialog.text = "Dios mio, ne kadar şanslı bir karşılaşma! Merhaba, monsieur "+GetFullName(pchar)+"! Santiago'da hoş karşılanan bir misafir olmuşsun. Kutsal Engizisyon için mi çalışıyorsun?";
			link.l1 = "Selamlar, señor "+npchar.name+". Bir daha asla görüşemeyeceğimizi sanmıştım, en azından dostça bir ortamda değil! Hayır, ben sadece Peder Vincento'yu ziyarete geldim. Peki ya sen? Artık Santiago'da mı görev yapıyorsun?";
			link.l1.go = "spa_prisoner_40";
		break;
		
		case "spa_prisoner_40":
			dialog.text = "After you freed me from arrest, I was compelled to stay in Santiago; it is not safe for me to return to Providence... but as you can see, I've kept my word. No Spanish ships in hot pursuit of you...";
			link.l1 = "İkimizin de sözünün eri olmasına sevindim.";
			link.l1.go = "spa_prisoner_41";
		break;
		
		case "spa_prisoner_41":
			dialog.text = "Dinle kaptan, bizim bu buluşmamıza, tabiri caizse, bir kadeh rom kaldırmaya ne dersin? Bir Fransıza bunu teklif edeceğim aklıma gelmezdi ama sen, señor, istisnasın.";
			link.l1 = "Elbette! Ağzımı biraz romla çalkalamaya hayır demem. Hadi meyhaneye gidelim.";
			link.l1.go = "spa_prisoner_42";
		break;
		
		case "spa_prisoner_42":
			DialogExit();
			NextDiag.CurrentNode = "spa_prisoner_43"; 
			FreeSitLocator("Santiago_tavern", "sit_front4");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Santiago_tavern", "sit", "sit_front4", "GuardOT_SpaOfficerInTavern", -1);
		break;
		
		case "spa_prisoner_43":
			LAi_SetSitType(Pchar);
			dialog.text = "Ah, şerefe!";
			link.l1 = "Ne içiyoruz, señor subay?";
			link.l1.go = "spa_prisoner_44";
		break;
		
		case "spa_prisoner_44":
			dialog.text = "Hadi, ikimizi de ilgilendiren ama tarafsız bir şeye içelim. Mesela, cesurca ve başarılı bir şekilde ülkesine hizmet etmeye! Hepimizin kendi ülkesi var!";
			link.l1 = "Ve bir de hükümdarlarımızın birbirleriyle anlaşmaya varmasını, Fransızlar ile İspanyolların hem anavatanlarında hem de Karayipler'de savaşmayı bırakmasını kutlayalım.";
			link.l1.go = "spa_prisoner_45";
		break;
		
		case "spa_prisoner_45":
			dialog.text = "Güzel söylediniz, kaptan! Barışa! Size İspanyol usulü içmeyi göstereceğim! Arriba, abajo, al centro y pa' dentro!";
			link.l1 = "Barışa... (içiyor)";
			link.l1.go = "spa_prisoner_46";
		break;
		
		case "spa_prisoner_46":
			dialog.text = "Aha! Küba romu gerçekten Karayipler'in en iyisi...";
			link.l1 = "Katılıyorum. Söylesene, St. Pierre’de yakalandığın için seni cezalandırmaya kalktılar mı?";
			link.l1.go = "spa_prisoner_47";
		break;
		
		case "spa_prisoner_47":
			dialog.text = "Neyse ki, sadece hafif bir ceza aldım. O felaket artık tamamen geride kaldı. Sonuçta burada, kolonilerde subaylara ihtiyaç var.";
			link.l1 = "Ve komutanın... adı neydi... Diego, değil mi? O başarısız baskın ona nasıl mal oldu? Rütbesi indirildi mi?";
			link.l1.go = "spa_prisoner_48";
		break;
		
		case "spa_prisoner_48":
			dialog.text = "Ah, hayır! Sevgili Diego de Montoya'mıza dokunulmaz, arkasında Don Ramon de Mendosa y Riba olduğu sürece. Bu arada, Don Diego dün daha Santiago'daydı. San Jose'den gelmişti.";
			link.l1 = "Yok artık? İlginçmiş! Neyse ki sokakta karşılaşmadık. Korkarım o mesele bir düelloyla sonuçlanabilirdi, haha!";
			link.l1.go = "spa_prisoner_49";
		break;
		
		case "spa_prisoner_49":
			dialog.text = "Don Diego'nun şu anda sizinle ilgilenecek vakti yok, kaptan. Şu an hayatını bir düelloda riske atamayacak kadar çok şeyi tehlikeye atıyor. Batı Ana'da Baron Mendoza'yla birlikte bir plan kurmuş. Havana'da bir filo topladı ve her an İspanya'ya dönmek üzere yola çıkmaya hazırlanıyor.";
			link.l1 = "Sen de onun tayfasında mısın?";
			link.l1.go = "spa_prisoner_50";
		break;
		
		case "spa_prisoner_50":
			dialog.text = "Hayır. Yarın Porto Riko'daki San Juan garnizonuna gidiyorum. Don Mendosa oradayken Providence'da artık istenmiyorum.";
			link.l1 = "O halde, yeni görevin için içelim; orada seni sadece mutlu günler ve güzel kızlar beklesin.";
			link.l1.go = "spa_prisoner_51";
		break;
		
		case "spa_prisoner_51":
			dialog.text = "Çok teşekkür ederim, monsieur. Size de her türlü iyi dileklerimi sunarım. Ah, sanırım artık gitme vakti geldi. Bu içkimi bitirip sonra sizi uğurlayacağım.";
			link.l1 = "Tanrı sizinle olsun, señor "+npchar.name+". Belki bir gün huzur içinde tekrar karşılaşırız.";
			link.l1.go = "spa_prisoner_52";
		break;
		
		case "spa_prisoner_52":
			DialogExit();
			AddDialogExitQuest("GuardOT_SpaOfficerOutTavern");
		break;
		
		case "spa_prisoner_53":
			PlaySound("Voice\English\other\OZGi-01.wav");
			dialog.text = "Just as I told you, Don Diego: the fish took the bait; hook, line, and sinker... Oh, looks like we meet again, monsieur. Unfortunately, not under the peaceful auspices that we wished.";
			link.l1 = ""+npchar.name+"? Vay canına! Bunu beklemiyordum. Nedense seni dürüst, soylu bir subay sanmıştım. Yanılmışım demek ki.";
			link.l1.go = "spa_prisoner_54";
		break;
		
		case "spa_prisoner_54":
			dialog.text = "Sana ne hak veriyor? Sözümü tuttum, sana sonsuz dostluk yemini etmedim. Hiçbir şey değişmedi, monsieur. Hâlâ İspanya'nın ve benim şahsi düşmanımsın. Burası Santiago değil, burada Peder Vincento yok ve onun o küçük geçiş izni de sana yardımcı olmayacak...";
			link.l1 = "Öyle mi diyorsun? Bence bir yandan rom içerken dostça sohbet edip, öte yandan beni tuzağa çekmeye çalışmak epeyce haince, sence de öyle değil mi, señor "+npchar.name+"?";
			link.l1.go = "spa_prisoner_55";
		break;
		
		case "spa_prisoner_55":
			dialog.text = "Bana hain mi diyorsun, seni maricón?!";
			link.l1 = "...";
			link.l1.go = "spa_prisoner_56";
		break;
		
		case "spa_prisoner_56":
			DialogExit();
			sld = CharacterFromID("Diego");
			sld.dialog.currentnode = "shore";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		// посланец Винсенто
		case "vinsentoagent":
			PlaySound("Voice\English\other\OZGi-02.wav");
			dialog.text = "Hey, sen! Evet, evet, sen! "+GetFullName(pchar)+"?";
			link.l1 = "Evet dostum. Benim.";
			link.l1.go = "vinsentoagent_1";			
		break;
		
		case "vinsentoagent_1":
			dialog.text = "Önemli birinden bir mektup aldım. Kimin olduğunu zaten biliyorsun.";
			link.l1 = "Biliyorum, ver şunu.";
			link.l1.go = "vinsentoagent_2";			
		break;
		
		case "vinsentoagent_2":
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento";
			dialog.text = "Buyur bakalım. Bunca zahmetim için birkaç kuruş vermez misin?";
			if (sti(Pchar.money) >= 2000)
			{
				link.l1 = "Biraz gümüş al. Bunu hak ettin, hem de alnının teriyle.";
				link.l1.go = "vinsentoagent_2_1";	
				AddCharacterExpToSkill(pchar, "Leadership", 50);
			}
			else
			{
				link.l1 = "Bana oyun mu oynuyorsun, dostum? Teslimat için zaten ödeme almıştın.";
				link.l1.go = "vinsentoagent_2_2";
			}
		break;
		
		case "vinsentoagent_2_1":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Sağ ol, delikanlı. Cömert bir beyefendiyle iş yapmak keyifti.";
			link.l1 = "Pekâlâ, defol git, burada olanlar hakkında tek kelime etme.";
			link.l1.go = "vinsentoagent_3";			
		break;
		
		case "vinsentoagent_2_2":
			dialog.text = "Havana Kurdu senin dostun...";
			link.l1 = "Ha? Hâlâ buradasın...";
			link.l1.go = "vinsentoagent_3";			
		break;
		
		case "vinsentoagent_3":
			DialogExit();
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
		break;
		
		// боцман Гая Марше
		case "boatsvandega":
			dialog.text = "'Admirable'a hoş geldiniz, Kaptan "+GetFullName(pchar)+"!";
			link.l1 = TimeGreeting()+" ! Şaşırtıcı. Beni tanıyor musun?";
			link.l1.go = "boatsvandega_1";			
		break;
		
		case "boatsvandega_1":
			dialog.text = "Fransız kolonilerinde   o büyük kaptanın adını duymayan kim kaldı ki "+GetFullName(pchar)+", St. Pierre'ye saldıran bir savaş gemisinin komutasındaki İspanyol filosunun dişlerini döken ve tüm düşman baskın birliğini yok eden kişi! Sen ulusal bir kahramansın!";
			link.l1 = "Aman Tanrım, hadi ama. 'Kahraman'... Ben sadece Fransa'ya görevini yerine getiren bir askerim.";
			link.l1.go = "boatsvandega_2";
		break;
		
		case "boatsvandega_2":
			dialog.text = "Senin yaptığını pek çok askerin yapabileceğini sanmıyorum, kaptan... Eh, seni meyhanede bir romla ağırlamak isterdim ama ne yazık ki: kaptan adamların bir damla bile rom içmesini yasakladı, ben de kötü örnek olmak istemem...";
			link.l1 = "Hm... Yani kendin kaptan değilsin?";
			link.l1.go = "boatsvandega_3";
		break;
		
		case "boatsvandega_3":
			dialog.text = "Ben kaptana mı benziyorum? Hoho! Hayır, ben sadece lostromoyum. Adım Serge Degas. Bizim kaptan, Gaius Marchais, bütün gününü meyhanede geçiriyor, biz de burada sözde bir 'tüccar' kervanını bekleyerek oyalanıyoruz. Kaptan denizcilere maaş borçlu, bize de öyle, bütün tayfa beş parasız kaldı.. ";
			link.l1 = "Ne oldu? İspanyol vanilya kervanı tüylerini yoldurmak için hâlâ ortada yok mu?";
			link.l1.go = "boatsvandega_4";
		break;
		
		case "boatsvandega_4":
			dialog.text = "Olmaz böyle şey! Kaptanımız bu gemiyi ele geçirdikten sonra korsanlığı bıraktı. Bakın, Avrupa'ya giden bir ticaret kervanının yakında Guadeloupe'a uğrayacağını ve vanilya satın alacaklarını duymuş. O yüzden Bridgetown'da ambarlarımızı ağzına kadar vanilyayla doldurdu! Sandı ki kasasını üç yüz peso kasaya satacak — evet, hayal işte!\nTabii biz vardığımızda ortada vanilya kervanı yoktu, buradaki yerlilere satmak ise zarar demekti. Şimdi de böyle bekliyoruz, şu 'tüccarlar' gelsin diye — bir gün gelirler belki, ya da üç yıl sonra... Kaptan bütün gün meyhanede oturup herkese dert oluyor, milleti bıktırıyor. Sadece gemiye dönüp sızmak için geliyor. Şimdi sonunda, zarar etmemek için kasasını iki yüz pesoya satmaya razı.\nBütün paramız o yüke gitti. Bir gün tayfa onu bağlayıp vanilyayı ucuza satacak, borçlarımızı kapatmak için... Yemin ederim, her an olabilir gibi geliyor bana.";
			link.l1 = "Evet... kaptanını ne üzüyor?";
			link.l1.go = "boatsvandega_5";
		break;
		
		case "boatsvandega_5":
			dialog.text = "Bir işi yapmaya değerse, hakkıyla yapmak gerekir. O ise ikisini de beceremiyor. Pazarlık yapmayı hiç bilmiyor. Yük taşımış olsaydı mesele başka olurdu, ama ille de kendini tüccar gibi hissetmek istedi. Umarım bir gece güverteden denize yuvarlanır...";
			link.l1 = "Seni anlıyorum, Serge. Merak etme, eminim bir gün senin... kervanın ortaya çıkacaktır.";
			link.l1.go = "boatsvandega_6";
		break;
		
		case "boatsvandega_6":
			dialog.text = "Ah, mucizelere inanmam kaptan. Belki bir gün tekrar karşılaşır, biraz rom içeriz... Şu an bir yudum rom için neler vermezdim...";
			link.l1 = "Bol şans, dostum.";
			link.l1.go = "boatsvandega_7";
		break;
		
		case "boatsvandega_7":
			DialogExit();
			NextDiag.currentnode = "boatsvandega_8";
			npchar.DeckDialogNode = "boatsvandega_8";
			// активируем каракку
			sld = characterFromId("GOT_Gevarra");
			sld.Dialog.Filename = "Quest\Sharlie\Guardoftruth.c";
			sld.DeckDialogNode = "gevarra";
			AddQuestRecord("Guardoftruth", "16");
		break;
		
		case "boatsvandega_8":
			dialog.text = "Eh, kaptan, bir yudum roma gerçekten ihtiyacım var!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "boatsvandega_8";
		break;
		
		// Гай Марше
		case "marshe_tavern":
			PlaySound("Voice\English\tavern\Kontrabandisti-08.wav");
			dialog.text = NPCStringReactionRepeat("Ho! Sen tüccar gemisinden değil misin? Hayır mı? Ah, özür dilerim. Tabii ki değilsin... Benim hatam.","Canım istemiyor, monsieur, o yüzden konuşacak başka birini bul.","Ah, yine sen mi?!","Hımm...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Boş ver, dostum. Böyle şeyler olur.","Biraz rom alın, kaptan. Dertlerinizi biraz olsun hafifletir...","Heyecan yapma dostum. Sağlığına zararlı.","Pekala, pekala. Gidiyorum.",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "marshe_tavern";
		break;
		
		case "marshe_lay":
			PlaySound("Voice\English\citizen\convict-03.wav");
			dialog.text = "Ah... Hm... Ne oluyor, bu da ne?..";
			link.l1 = "Sessiz ol, dostum... Hiç ses çıkarma...";
			link.l1.go = "marshe_lay_1";
		break;
		
		case "marshe_lay_1":
			PlaySound("Voice\English\citizen\convict-02.wav");
			dialog.text = "Ha? Ne? Kahretsin!";
			link.l1 = "";
			link.l1.go = "marshe_lay_2";
		break;
		
		case "marshe_lay_2":
			DialogExit();
			LAi_SetgroundSitType(npchar);
			NextDiag.currentnode = "marshe_sitground";
		break;
		
		case "marshe_sitground":
			PlaySound("Voice\English\EvilPirates07.wav");
			dialog.text = "Aaah! Sen kimsin? Benden ne istiyorsun?";
			link.l1 = "Eğer çeneni kapamazsan, dişlerini dökerim, anladın mı? Bu gemiyi ele geçirirken aldığın kutsal eşyalar nerede?";
			link.l1.go = "marshe_sitground_1";
		break;
		
		case "marshe_sitground_1":
			dialog.text = "Hangi gemiler? Neden bahsettiğini bilmiyorum! Bu benim gemim!";
			link.l1 = "Senin gemin mi? Daha düne kadar adı 'Santa Margarita'ydı ve İspanyol bayrağı altında yol alıyordu... Sana soruyorum, o kutsal eşyalar nerede? Altın bir monstrans, lazurit taşlı bir haç ve altın bir buhurdan? Onlara ne yaptın? Satmadın, değil mi?";
			link.l1.go = "marshe_sitground_2";
		break;
		
		case "marshe_sitground_2":
			dialog.text = "Tanrım, kulaklarıma inanamıyorum... sen İspanyol musun? Hayır... İspanyol değilsin! Fransızsın! Bu daha da kötü! O aşağılık Kastilyalılara satılmışsın! Fransızların ruhu artık kaça gidiyor, ha? Sana hiçbir şey söylemeyeceğim, hain! O süslü şeylere elini süremeyeceksin!";
			link.l1 = "Tek kelime yok, öyle mi? Bana uyar. Sorgu için burası pek uygun sayılmaz zaten... Şimdi seni konuşturmasın diye ağzını bağlayacağız, sonra da seni sandalıma götüreceğiz... Eninde sonunda konuşacaksın. Bundan hiç şüphem yok.";
			link.l1.go = "marshe_sitground_3";
		break;
		
		case "marshe_sitground_3":
			dialog.text = "Sen seni İspanyollara satan hain! En iyisi...";
			link.l1 = "Sessiz ol, alçak... Hemen arkamdan gel yoksa seni yere serer, ayaklarından tutup güverte boyunca sürüklerim.";
			link.l1.go = "marshe_sitground_4";
		break;
		
		case "marshe_sitground_4":
			DialogExit();
			RemoveAllCharacterItems(npchar, true);
			ChangeCharacterAddressGroup(npchar, "Deck_Galeon_Ship", "goto", "stand");
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1 = "locator";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.location = "Deck_Galeon_Ship";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator_group = "reload";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator = "reload2";
			pchar.quest.GuardOT_marchfromgaleon.function = "GuardOT_ExitGaleon";
		break;
		
		// капитан каракки - Карлос Геварра
		case "gevarra":
			dialog.text = "Size nasıl yardımcı olabilirim, efendim?";
			link.l1 = "Nasılsınız, kaptan? Basse-Terre'e ne vesileyle geldiniz? Bildiğim kadarıyla, Hollanda bayrağı altında seyreden bir İspanyolsunuz?";
			link.l1.go = "gevarra_1";			
		break;
		
		case "gevarra_1":
			dialog.text = "Ne oldu efendim? Evet, İspanyolum. Bunu ismimden ve gemimin tipinden anlamak zor değil, ama burada tamamen yasal olarak bulunuyorum. Hollanda Batı Hindistan Şirketi'nden lisansım var, yani...";
			link.l1 = "Panik yapmayın, señor! Aslında İspanyol olmanıza çok sevindik... Söyleyin bakalım, buraya ithalat için mi geldiniz, yoksa ihracat için mi?";
			link.l1.go = "gevarra_2";			
		break;
		
		case "gevarra_2":
			dialog.text = "Havana'dan mal getirdim ve burada, yerel pazarda sattım. Şimdi ise, gemimin ambarı boş dönmesin diye kârlı bir yük bekliyorum.";
			link.l1 = "Señor, size bir iş teklifim var! Bana yardım ederseniz iyi para kazanabilirsiniz. Konuşalım mı? Bu arada, adınız nedir?";
			link.l1.go = "gevarra_3";			
		break;
		
		case "gevarra_3":
			dialog.text = "Carlos. Kaptan Carlos Guevara. Teklifiniz nedir?";
			link.l1 = "Küba'ya, adı   olan bir adama bir miktar vanilya satın alıp göndermem gerekiyor "+pchar.questTemp.Guardoftruth.LMname+", Santiago deniz fenerinin bekçisiyim. Fakat ciddi bir sorunum var. Öncelikle, hiçbir dükkânda ihtiyacım olan kadar vanilya yok...";
			link.l1.go = "gevarra_4";			
		break;
		
		case "gevarra_4":
			dialog.text = "";
			link.l1 = "İkincisi, derhal St. Christopher'a gitmem gerekiyor ve ne kadar süreyle uzak kalacağımı bilmiyorum. Her geçen gün para kaybediyorum, anlıyor musun? Bu tam bir rezalet!";
			link.l1.go = "gevarra_5";			
		break;
		
		case "gevarra_5":
			dialog.text = "Anlıyorum. Qué lástima, señor. Sonuçta, dünyadaki tüm parayı kazanamazsınız. Peki, benden ne istiyorsunuz?";
			link.l1 = "Şuraya bak. Şu kalyonu görüyor musun? İçinde bana çok lazım olan vanilya dolu. Sorun şu ki, kalyonun kaptanının aklına bir baharat kervanının yakında buraya geleceği ve yükünü kârla, neredeyse sandık başına üç yüz peso'ya satın alacağı gibi bir saçmalık girmiş!";
			link.l1.go = "gevarra_6";			
		break;
		
		case "gevarra_6":
			dialog.text = "Yes, there are a lot of naive men around these days; a fool and his money are soon parted...";
			link.l1 = "Saf olmak bir şey, ama bu adam düpedüz aptal! Vanilyasını iki yüz on pesoya almak istedim, burada dükkanda iki yüz bile etmez. İnanabiliyor musun, bana defol git dedi! Sadece iki yüz elliye satacağını söyledi!";
			link.l1.go = "gevarra_7";			
		break;
		
		case "gevarra_7":
			dialog.text = "Haha! Ne aptal!";
			link.l1 = "Evet! Aslında ona tam olarak bunu söyledim. Tabii ki bana kızdı... ama o vanilyaya gerçekten ihtiyacım var! İşte teklifim, señor. Ben bir tüccar değilim, ama siz pazarlık sanatında gerçek bir ustasınız diye düşünüyorum. Üstelik geniş bir ambarınız var...";
			link.l1.go = "gevarra_8";			
		break;
		
		case "gevarra_8":
			dialog.text = "";
			link.l1 = "Şu lanet aptalı yükü sana satmaya ikna et. Ben onu yüzüne karşı aşağıladıktan sonra bana artık satmaz. Kutu başına iki yüz on peso ödemeye hazırım. Fiyatı düşürürsen, aradaki farkı kendine al. Bunun karşılığında da, vanilyayı Santiago'ya götürmen için tekneni kiralayacağım.";
			link.l1.go = "gevarra_9";			
		break;
		
		case "gevarra_9":
			dialog.text = "Bana bu sevkiyat için ne kadar ödemeye hazırsın?";
			link.l1 = "Ne kadar istiyorsun?";
			link.l1.go = "gevarra_10";			
		break;
		
		case "gevarra_10":
			dialog.text = "Santiago oldukça uzak... otuz bin peso.";
			link.l1 = "Bu fazla oldu, dostum. Biraz da sen fedakârlık yap.";
			link.l1.go = "gevarra_11";			
		break;
		
		case "gevarra_11":
			dialog.text = "Pekâlâ, zaten yolumun üstünde... Yirmi beş bin ve bir kuruş bile eksik olmaz.";
			link.l1 = "Sorun değil. Galyonun kaptanının adı Gaius Marchais. Bütün gününü meyhanede surat asarak geçiriyor. Umarım baharatlarını satmaya ikna edebilirsin.";
			link.l1.go = "gevarra_12";			
		break;
		
		case "gevarra_12":
			dialog.text = "Daha önce daha büyük ahmaklarla iş yaptım. Ona, malları gökten inme fiyatlara alacakmış gibi gösterilen kervan hakkındaki dedikoduları kimlerin yaydığını en ince ayrıntısına kadar anlatacağım. Onu, bütün bunların kafasında kurduğu hayallerden ibaret olduğuna inandırdığımda, satacak. Bundan eminim.";
			link.l1 = "Yani, anlaştık mı?";
			link.l1.go = "gevarra_13";			
		break;
		
		case "gevarra_13":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			dialog.text = "Vanilya ve nakliye için paran varsa, anlaştık demektir. Sevimli bir İrlanda atasözünde dendiği gibi: 'Parayı göster.'";
			if (sti(Pchar.money) >= iTemp)
			{
				link.l1 = "Al bakalım, göz at. Hepsi burada.";
				link.l1.go = "gevarra_14";
			}
			else
			{
				link.l1 = "Gümüş gemimde. Gidip alacağım ve hemen döneceğim!";
				link.l1.go = "gevarra_14_no";
			}
		break;
		
		case "gevarra_14_no":
			DialogExit();
			NextDiag.currentnode = "gevarra_wait";
			npchar.DeckDialogNode = "gevarra_wait";
		break;
		
		case "gevarra_wait":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			dialog.text = "Parayı getirdin mi?";
			if (sti(Pchar.money) >= iTemp)
			{
				link.l1 = "Al bakalım, göz at. Hepsi burada.";
				link.l1.go = "gevarra_14";
			}
			else
			{
				link.l1 = "Hemen şimdi alıyorum!";
				link.l1.go = "exit";
			}	
		break;
		
		case "gevarra_14":
			if (stf(environment.time) < 24.0)
			{
				sTemp = "tomorrow";
				iTemp = 1;
			}
			else
			{
				sTemp = "today";
				iTemp = 0;
			}
			if (stf(environment.time) > 21.0 && stf(environment.time) < 7.0)
			{
				dialog.text = "Harika! Akıllı ortaklarla iş yapmaktan gerçekten keyif alıyorum. Yine beklerim "+sTemp+" sabah on civarında. O saate kadar ortak dostumuz Gaius'un kendine geleceğini düşünüyorum.";
				link.l1 = "Harika! Sonra görüşürüz!";
				link.l1.go = "gevarra_15";
				pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour  = 10.0;
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
			}
			else
			{
				dialog.text = "Harika! Akıllı ortaklarla iş yapmaktan gerçekten keyif alıyorum. Ben kıyıya gidiyorum. Üç saat sonra tekrar gel. O zamana kadar ortak dostumuz Gaius'un da aklı başına gelmiş olur sanırım.";
				link.l1 = "Harika! Sonra görüşürüz!";
				link.l1.go = "gevarra_15";
				pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour  = sti(GetTime()+3);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
			}
		break;
		
		case "gevarra_15":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			DialogExit();
			NextDiag.currentnode = "gevarra_time";
			npchar.DeckDialogNode = "gevarra_time";
			AddMoneyToCharacter(pchar, -iTemp); // деньги сразу списываем
			bQuestDisableMapEnter = true;
			pchar.GenQuest.MapClosedNoBattle = true;
			AddQuestRecord("Guardoftruth", "17");
			AddCharacterExpToSkill(pchar, "Sneak", 50);
		break;
		
		case "gevarra_time":
			dialog.text = "Señor, rolümü iyi hatırlıyorum. Merak etmeyin, o sert biri olabilir ama onu çözerim.";
			link.l1 = "Teşekkür ederim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "gevarra_time";
		break;
		
		case "gevarra_16":
			dialog.text = "İş tamam, señor. Zavallı adam vanilyasını almak istediğime öylesine sevindi ki, avans sayarken elleri mutluluktan titriyordu – ya da belki de sadece içtiği romdandı. Yarın öğle vakti Capster Plajı’nda yüklemeyi yapacağız, limandaki gümrükçülerin dikkatini çekmemek için.\nYükü gemiye aldıktan sonra hemen Santiago’ya yelken açacağım. Oradaki teslimattan sonra vanilyayı fenerdeki ortağınıza teslim edip ona devredeceğim. Ona iletmemi istediğiniz bir mesaj var mı?";
			link.l1 = "Evet. İşte bir mektup. Anlaşmanın yarın öğlen Capster Plajı'nda olacağını söylüyorsun? Peki, o zaman, bir şey olursa adadan uzakta, burun açıklarında demirleyeceğim.";
			link.l1.go = "gevarra_17";
		break;
		
		case "gevarra_17":
			Log_Info("You handed the letter over");
			PlaySound("interface\important_item.wav");
			dialog.text = "Bana güvenebilirsiniz, señor. Ben dürüst bir adamım. Ayrıca sizinle tartışmak gibi bir niyetim yok, tüccar için itibar her şeydir. Ama isterseniz izleyip kontrol edebilirsiniz, benim için hiç sorun değil.";
			link.l1 = " Minnettarım, señor. Yarın anlaşmayı gözeteceğim ve siz yelken açar açmaz, St. Christopher'daki işlerime bakacağım.";
			link.l1.go = "gevarra_18";
		break;
		
		case "gevarra_18":
			DialogExit();
			NextDiag.currentnode = "gevarra_exit";
			npchar.DeckDialogNode = "gevarra_exit";
			bQuestDisableMapEnter = true;
			pchar.GenQuest.MapClosedNoBattle = true;
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			AddQuestRecord("Guardoftruth", "18");
			pchar.quest.GuardOT_gotoshore.win_condition.l1 = "ExitFromSea";
			pchar.quest.GuardOT_gotoshore.function = "GuardOT_TradeComplete";
		break;
		
		case "gevarra_exit":
			dialog.text = "Kaptan, sizi temin ederim: sizi hayal kırıklığına uğratmayacağım ve anlaşmamızın tüm şartlarını eksiksiz yerine getireceğim.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "gevarra_exit";
		break;
		
		// матросы Марше
		case "marshe_sailor":
			dialog.text = LinkRandPhrase("Hik! Y-yaşasın! Bizim eski kaptan sonunda paramızı verdi! K-kaptana üç kere yaşasın! Hik!","Bardakta mı geliyor?! Ben de bir tane alıyorum!","Kesemiz dolu, kadınlarımız daha da dolgun olsun! Yaşasın!","Ve işte orada yatıyorlardı, hepsi iyi ama ölü adamlar, hık! Sanki bir meyhanede gün doğumu gibi. Yo ho ho ve bir şişe rom!","Yo ho ho ve bir şişe rom!");
			link.l1 = LinkRandPhrase("Ay, dostum.","Sence zaten yeterince rom içmedin mi?","İçki ve şeytan diğerlerinin işini bitirdi...");
			link.l1.go = "exit";
		break;
		
		case "galeonguard":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "Dur! Kim var orada? Alarm! Saldırganları püskürtün!";
			link.l1 = "...";
			link.l1.go = "galeonguard_1";
		break;
		
		case "galeonguard_1":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.CantRun");
			CheckAndSetOverloadMode(GetMainCharacter());
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Attack");
			LAi_RemoveCheckMinHP(pchar);
			GuardOT_GaleonGuardFightAdd();
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_galeonguard_"+i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, "GaleonFight");
			}
			LAi_group_FightGroups("GaleonFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// англичане в бухте
		case "dominica_hunter":
			dialog.text = "Ha ha! Sen de Rollie the Cap'in hazinesi için mi geldin, ha? Biz aradık da aradık, ama bir türlü bulamadık. Keşke şu ahmaklardan biri en azından şelalenin arkasından yüzüp çıkıntıya ulaşmayı akıl edebilseydi!";
			link.l1 = "Sen Albay Fox'un adamlarından birisin, değil mi?";
			link.l1.go = "dominica_hunter_1";
		break;
		
		case "dominica_hunter_1":
			dialog.text = "Deniz Tilkileriyle bağlantılarım olabilir. Bilmen gerekmiyor, bunun bir anlamı yok. Şu anda hiçbir şey bilmen gerekmiyor. Hazinemi buldun, bunun için sana büyük bir teşekkür borçluyuz...";
			link.l1 = "Anladım. Sen bir Deniz Tilkisi değilsin, daha çok bir deniz köpeği... ya da bir çakal gibisin. Hangisi sana daha çok yakışıyor?";
			link.l1.go = "dominica_hunter_2";
		break;
		
		case "dominica_hunter_2":
			dialog.text = "Görünüşe bakılırsa elimizde bir doğa filozofu var, beyler. Hayvanlar alemi konusunda tam bir uzman!";
			link.l1 = "Kılıcımın keskinliğini denemek ister misin, çakal?";
			link.l1.go = "dominica_hunter_3";
		break;
		
		case "dominica_hunter_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_DH_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_HuntersDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// Белинда Риберо
		case "belinda":
			dialog.text = TimeGreeting()+", señor. Size nasıl yardımcı olabilirim?";
			link.l1 = "Merhaba. Siz Doña Belinda de Ribero musunuz?";
			link.l1.go = "belinda_1";
		break;
		
		case "belinda_1":
			dialog.text = "Evet, benim. Kiminle konuşma şerefine nail oldum?";
			link.l1 = "Kaptan "+GetFullName(pchar)+", madam. Please don't be put off by my French surname; at the moment, I'm fulfilling an assignment from the Right Reverend Inquisitor of Santiago, Father Vincento.";
			link.l1.go = "belinda_2";
		break;
		
		case "belinda_2":
			dialog.text = "Ne kadar ilginç! Kutsal Mahkeme ve İsa Cemiyeti'nin her milletten ve sınıftan insanlarla dolu olduğunu duymuştum ama şimdiye kadar onlar için çalışan bir yabancıyla hiç tanışmamıştım. Size nasıl yardımcı olabilirim, señor?";
			link.l1 = "Sizde, Saygıdeğer Rahip Baba'nın büyük ilgi gösterdiği bir eşya var. Willemstad'daki bankacıdan kısa süre önce aldığınız altın bir monstrans, yani bir ayin sunacağı.";
			link.l1.go = "belinda_3";
		break;
		
		case "belinda_3":
			dialog.text = "Oldukça iyi bilgilendirilmişsiniz, señor. Kimin için çalıştığınızı bildiğimden, bu beni şaşırtmamalı. Evet, monstransı ben aldım; böylesine değerli bir şey, çalınmış ıvır zıvırların ve rehin bırakılmış eşyaların arasında, bir tüccarın dükkanında öylece durmamalıydı.";
			link.l1 = "Monstransı yanınızda mı, madam?";
			link.l1.go = "belinda_4";
		break;
		
		case "belinda_4":
			dialog.text = "Evet. Onu mahallemizin kilisesine hediye etmeyi düşünmüştüm, ama burada başıma o kadar çok şey geldi ki... Yapamadım... Ah, özür dilerim...";
			link.l1 = "Ağlıyor musunuz, hanımefendi? Sözlerim sizi üzdü mü? Eğer öyleyse, lütfen beni affedin.";
			link.l1.go = "belinda_5";
		break;
		
		case "belinda_5":
			dialog.text = "Ah, lütfen señor... Sohbetimize dönelim. Anladığım kadarıyla, Baba Vincento bu monstransı istiyor? Onu size vermemi ister misiniz?";
			link.l1 = "Bu değerli kap, Santiago’daki katedral için hazırlanmıştı, fakat sıradan bir korsan tarafından ele geçirilip birkaç kutsal eşyayla birlikte bir tefeciye satılmış. Benim görevim, çalınanları hak ettikleri yere geri götürmek. Elbette, masraflarınızı tamamen karşılayacağım.";
			link.l1.go = "belinda_6";
		break;
		
		case "belinda_6":
			dialog.text = "Ah, lütfen yapmayın! Gerçekten bu paranın benim için bu kadar önemli olduğunu mu sanıyorsunuz? Bu monstransı Aziz Anne Kilisesi için aldım ve onu gerçek sahibine, hele ki Cizvit Tarikatı'ndan Peder Vincento'ya hizmet eden birine, hiç tereddüt etmeden teslim ederim. Fakat beni derinden rahatsız eden başka bir mesele var. Kilisenin sadık bir kızı olarak bana yardım edebilir misiniz?";
			link.l1 = "Hanımefendi, siz soylu bir bayansınız. Sizi ne üzüyor? Size nasıl yardımcı olabilirim?";
			link.l1.go = "belinda_7";
		break;
		
		case "belinda_7":
			dialog.text = "Ah, ama señor... Bir Cizvit kardeşinden bizzat yardım istemeye cesaret edemezdim. Sizler her zaman öylesine meşgulsünüz ki...";
			link.l1 = "Zaten yaptın. Sorun ne?";
			link.l1.go = "belinda_8";
		break;
		
		case "belinda_8":
			dialog.text = "Bana söz verebilir misiniz, Kutsal Kilise'nin bir temsilcisi olarak, sizden ne istediğimi kimsenin asla öğrenmeyeceğine?";
			link.l1 = "Sana namusum ve şerefim üzerine söz veriyorum, señora. Bu bir günah çıkarma sırrı değil belki, ama bu konuda kimseye tek kelime etmeyeceğim.";
			link.l1.go = "belinda_9";
		break;
		
		case "belinda_9":
			dialog.text = "Pekala. Sana güveniyorum. Çok değerli dostum Esteban Sosa başını belaya soktu. Seyahat ederken haydutlar tarafından yakalandı ve onlar yüz bin peso fidye istiyorlar. O kadar param yok, sadece harçlığımdan toplam miktarın yarısını biriktirebildim. Böyle bir konuda kimseden yardım isteyemem çünkü eğer yardım istersem onu öldüreceklerine yemin ettiler\nÜstelik sevgili... dostum için endişeleniyorum ve en kötüsünden korkuyorum. Parayı alır almaz onu öldürebilirler, böylece muhafızlara onları anlatamayacağından emin olurlar. Belki sen, cesur bir kaptan, bir Hristiyan ve Cemiyetin bir kardeşi olarak, haydutları elimdeki parayı kabul etmeye ve ona zarar vermemeye ikna edebilirsin...";
			link.l1 = "Değiş tokuş ne zaman ve nerede gerçekleşecek?";
			link.l1.go = "belinda_10";
		break;
		
		case "belinda_10":
			dialog.text = "Liderleri Bartie the Knacker adında bir adam. Esteban'ın fidyesini almak için her gece saat on birden gece yarısına kadar ormandaki mağara girişinde bekleyeceğini söyledi...";
			link.l1 = "Bunlar alışılmadık derecede özel şartlar...";
			link.l1.go = "belinda_11";
		break;
		
		case "belinda_11":
			dialog.text = "Görünüşe göre fidyenin tamamını hemen toplamamı istediler ve kimseden yardım istememi de istemediler... ama o kadar parayı bulamam, asla başaramam!";
			link.l1 = "Ağlamayın, hanımefendi. Size yardım etmeye çalışacağım. İsa Cemiyeti'nin bir kardeşi, dürüst bir Hristiyan kadını asla tehlikede bırakmaz.";
			link.l1.go = "belinda_12";
		break;
		
		case "belinda_12":
			dialog.text = "Sana güvenmekten başka çarem yok... Ama kaptan, Bartie the Knacker ayrıca fidyeyi getiren tek başına gelmezse ya da ben askerlere gidersem zavallı Esteban'ı hemen öldüreceğini söyledi!";
			link.l1 = "Bunu aklımda tutacağım.";
			link.l1.go = "belinda_13";
		break;
		
		case "belinda_13":
			dialog.text = "Al, bunu al. Bir araya getirebildiğim elli bin peso burada. O haydutları en azından bunu kabul etmeye ikna et. Onlara başka bir kuruşum kalmadığını söyle! Esteban'ı geri getir! Bunu başarırsan, kutsal sunak lambasını memnuniyetle Peder Vincento'ya vereceğim.";
			link.l1 = "Elimden gelen her şeyi yapacağım, madam. En iyisini umalım.";
			link.l1.go = "belinda_14";
		break;
		
		case "belinda_14":
			dialog.text = "Tanrı yardımcın olsun, cesur kaptan! Senin için dua edeceğim!";
			link.l1 = "...";
			link.l1.go = "belinda_15";
		break;
		
		case "belinda_15":
			AddMoneyToCharacter(pchar, 50000);
			DialogExit();
			NextDiag.CurrentNode = "belinda_16";
			AddQuestRecord("Guardoftruth", "31");
			bQuestDisableMapEnter = true;//закрыть карту
			locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", true);
			LAi_LocationDisableOfficersGen("Cumana_Cave", true);
			pchar.quest.GuardOT_gotocave.win_condition.l1 = "location";
			pchar.quest.GuardOT_gotocave.win_condition.l1.location = "Cumana_CaveEntrance";
			pchar.quest.GuardOT_gotocave.win_condition.l2 = "HardHour";
			pchar.quest.GuardOT_gotocave.win_condition.l2.hour = 23.00;
			pchar.quest.GuardOT_gotocave.function = "GuardOT_InCaveEntrance";
		break;
		
		case "belinda_16":
			dialog.text = "Kaptan, bir haber var mı?";
			link.l1 = "Henüz değil. Sadece bekleyin, señora. Sizi hayal kırıklığına uğratmayacağım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "belinda_16";
		break;
		
		case "belinda_17":
			dialog.text = "Bir haberiniz var mı, kaptan?";
			link.l1 = "Evet, señora. Korkarım iyi haberlerim yok.";
			link.l1.go = "belinda_18";
		break;
		
		case "belinda_18":
			dialog.text = "Söyle bana, beni bekletme! Haydutlarla karşılaştın mı?";
			if (sti(Pchar.money) >= 50000)
			{
				link.l1 = "Al, elli binini geri al. İhtiyacım olmadı. Bu yüzüğü de al. Tanıdık geleceğine inanıyorum.";
				link.l1.go = "belinda_19_1";
			}
			link.l2 = "Al, bu yüzüğü al. Sanırım sana tanıdık gelecektir.";
			link.l2.go = "belinda_19_2";
		break;
		
		case "belinda_19_1":
			RemoveItems(pchar, "jewelry29", 1);
			PlaySound("interface\important_item.wav");
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "Evet... evet, tanıdık geliyor. Esteban'a ne oldu?";
			link.l1 = "Mağarada haydutları buldum, dediğiniz gibi. 'Bartie the Knacker' ve Esteban Sosa aynı kişiymiş. Kaçırılma olayını sizi şantajla tehdit etmek için kendisi düzenlemiş. Bana sizin... ilişkinizden bahsetti. Ayrıca artık sizi görmek istemediğini de söyledi. Ona verdiğiniz yüzüğü kanıt olarak aldım.";
			link.l1.go = "belinda_20";
		break;
		
		case "belinda_19_2":
			dialog.text = "Bu... evet, evet, biliyorum. Esteban'a ne oldu?";
			link.l1 = "Mağarada haydutları buldum, dediğin gibi. Bana saldırdılar, beni bağladılar ve paranı aldılar. 'Bartie the Knacker' ve Esteban Sosa aynı kişiymiş. Kaçırılma olayını seni soymak için planlamış. Bana seninle olan... ilişkinizden bahsetti. Esteban beni serbest bıraktı ve kanıt olarak bu yüzüğü verdi. Bir daha asla onu göremeyeceğini söyledi.";
			link.l1.go = "belinda_20";
			npchar.quest.nomoney = true;
		break;
		
		case "belinda_20":
			if (CheckAttribute(npchar, "quest.nomoney")) sTemp = "";
			else sTemp = "I taught him a lesson, but I didn't kill him out of respect to you.";
			dialog.text = "Dios mio! Kulaklarıma inanamıyorum! Neden bütün bunlar benim başıma geliyor, neden?! Ona ne yaptım ki....";
			link.l1 = "Señora, yalvarırım, kendinizi bunun için suçlamayın. O rezil adam bir damla gözyaşınıza bile değmez. "+sTemp+"";
			link.l1.go = "belinda_21";
		break;
		
		case "belinda_21":
			if (CheckAttribute(npchar, "quest.nomoney")) sTemp = "";
			else sTemp = "And besides that, here's a gift to keep up your courage.";
			dialog.text = "Oh... Sakin olmaya çalışacağım. Señor, yardımınız için size teşekkür etmeliyim. Buyurun, işte monstransınız. "+sTemp+" Vaya con Dios.";
			link.l1 = "Teşekkür ederim, hanımefendi. Merak etmeyin, mağarada olanları kimse öğrenmeyecek. Biz Cizvitler her zaman sözümüzde dururuz. Şimdi müsaadenizle, gitmem gerek.";
			link.l1.go = "belinda_22";
		break;
		
		case "belinda_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "33");
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 3;
			GiveItem2Character(pchar, "jewelry33");
			Log_Info("You've received a gold ostensory");
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(npchar, "quest.nomoney"))
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				OfficersReaction("bad");
			}
			else
			{
				Log_Info("You've received an amulet");
				GiveItem2Character(pchar, "amulet_7");
				ChangeCharacterComplexReputation(pchar, "nobility", 5);
				OfficersReaction("good");
				ChangeCharacterNationReputation(pchar, SPAIN, 3);
				AddCharacterExpToSkill(pchar, "Leadership", 300);
			}
		break;
		
		// бандит Эстебана
		case "bandos_mush":
			PlaySound("Voice\English\other\OZGi-04.wav");
			dialog.text = "Olduğun yerde kal!";
			link.l1 = "Tam burada duruyorum.";
			link.l1.go = "bandos_mush_1";
		break;
		
		case "bandos_mush_1":
			dialog.text = "Parayı getirdin mi?";
			link.l1 = "Ne saçma bir soru. Hayır, buraya Manga Rosas toplamaya geldim... Sence başka neden gelmiş olabilirim ki?";
			link.l1.go = "bandos_mush_2";
		break;
		
		case "bandos_mush_2":
			dialog.text = "Oh ho ho! Komedyen ha! Hadi bakalım, mağaraya gir, Bartie seni bekliyor.";
			link.l1 = "Sen gerçekten tecrübeli bir muhafızsın... bu tavırla Kral Philip'in kendisini bile koruyabilirsin. Ben kendim içeri girerim.";
			link.l1.go = "bandos_mush_3";
		break;
		
		case "bandos_mush_3":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", true);
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.GuardOT_incave.win_condition.l1 = "location";
			pchar.quest.GuardOT_incave.win_condition.l1.location = "Cumana_Cave";
			pchar.quest.GuardOT_incave.function = "GuardOT_InCumanaCave";
		break;
		
		// Эстебан-Барти
		case "barty":
			PlaySound("Voice\English\other\OZGi-03.wav");
			dialog.text = "Beni beklettin... Parayı yanında getirdin mi?";
			link.l1 = "Bartie the Knacker sen misin? Bana sıradan bir hayduta pek benzemiyorsun.";
			link.l1.go = "barty_1";
		break;
		
		case "barty_1":
			dialog.text = "Neden nasıl göründüğümü umursuyorsun? Lanet parayı getirdin mi, getirmedin mi?";
			link.l1 = "Rehine nerede?";
			link.l1.go = "barty_2";
		break;
		
		case "barty_2":
			dialog.text = "Rehinenizi alacaksınız. Hadi, ver parayı. Beni kızdırma, çocuk.";
			link.l1 = "Bartie, ben aptal mıyım sence? Esteban Sosa'yı sağ ve sapasağlam görmeden, sana tek kuruş vermem. Nerede o?";
			link.l1.go = "barty_3";
		break;
		
		case "barty_3":
			dialog.text = "Ha, ayak diretiyorsun demek? Peki, sana iyi bir ders vereceğiz... Çocuklar, şu pisliği paramparça edelim!";
			link.l1 = "Piç!";
			link.l1.go = "barty_4";
		break;
		
		case "barty_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			GuardOT_InCumanaCaveEnemyAdd();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GOT_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_CumanaCaveBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			// офицеров насильно
			LAi_LocationDisableOfficersGen("Cumana_Cave", false); //офицеров пускать
			DoQuestFunctionDelay("GuardOT_SetOfficerCumanaCave", 3.0);
		break;
		
		case "barty_5":
			PlaySound("Voice\English\other\Plennie-02.wav");
			dialog.text = "";
			link.l1 = "Bu kadar dans yeter mi sana? Esteban Sosa nerede? Hadi, söyle yoksa kafanı suyun altına sokup baloncuklar bitene kadar bekletirim!";
			link.l1.go = "barty_6";
		break;
		
		case "barty_6":
			dialog.text = "Hayır... Lütfen bana zarar verme! Ben Esteban Sosa'yım.";
			link.l1 = "Ne?";
			link.l1.go = "barty_7";
		break;
		
		case "barty_7":
			dialog.text = "Evet, evet. Ben Bartie the Knacker değilim. Ben sadece...";
			link.l1 = "Senora de Ribero'dan yüz bin peso koparmak için kendini 'kaçırttın', ha, seni alçak?!";
			link.l1.go = "barty_8";
		break;
		
		case "barty_8":
			dialog.text = "Beni anlamalısın, erkek erkeğe konuşuyoruz. Belinda... Onun bu takıntılı aşkı beni gerçekten bezdirdi. Sürekli peşimde, gece gündüz rahat yok, adamım! Kocası bile artık bizden şüphelenmeye başladı, hem de yarı kör haliyle!";
			link.l1 = "Bak sen şu işe! Demek sevgilisiniz?";
			link.l1.go = "barty_9";
		break;
		
		case "barty_9":
			dialog.text = "Artık değil. Ondan yeni kaçtım.";
			link.l1 = "Yola çıkmadan biraz para almaya karar verdin, öyle mi? Peki, şimdi seninle ne yapayım? Beni öldürüp ormana saklamaya çalıştığın gibi, şimdi de senin cesedini mi saklayayım?";
			link.l1.go = "barty_10";
		break;
		
		case "barty_10":
			dialog.text = "Hayır! Kan dökülmesini istemedim, yemin ederim!";
			link.l1 = "Bu yüzden mi köpeklerini üstüme saldın?";
			link.l1.go = "barty_11";
		break;
		
		case "barty_11":
			dialog.text = "Sadece ceplerini boşaltmanı isteyecektik, hepsi bu!";
			link.l1 = "Ve beni selvada çıplak mı bırakacaksın? Seni gemimin en yüksek serenine asmalı, orada sallandırmalıyım, seni alçak! Ama bunu yapmayacağım, sırf seninle uğraşmak zorunda kalan o iyi kadına duyduğum saygıdan. Biliyor musun? Aslında seni onun yanına götürüp ne yapacağına kendisinin karar vermesini sağlamalıyım.";
			link.l1.go = "barty_12";
		break;
		
		case "barty_12":
			dialog.text = "Hayır, ama o hariç her şey! Cumana'ya geri dönmeyeceğim!";
			link.l1 = "Bu mağarada sonsuza kadar kalmayı mı tercih edersin?";
			link.l1.go = "barty_13";
		break;
		
		case "barty_13":
			dialog.text = "Beni bağışlayın, señor! Bırakın gideyim, buradan uzaklara yelken açacağım ve bir daha asla Cumana'ya dönmeyeceğim! Belinda'nın kocasının beni düelloda doğramasını ya da peşimden bir suikastçı göndermesini bekleyecek değilim!";
			link.l1 = "Peki. Señora de Ribero'nun hatırı için seni ona götürmeyeceğim. Ama sakın bunun üstünün kolayca örtüleceğini sanma. O, flört etmeye kalktığı zavallı aşağılık herifi mutlaka öğrenecek. Onun tanıyabileceği neyin var, hangi işaretleri gösterebilirsin?";
			link.l1.go = "barty_14";
		break;
		
		case "barty_14":
			dialog.text = "Bak. Şu turkuaz yüzük var ya, onu bana bizzat kendisi verdi.";
			link.l1 = "Mükemmel. Onu buraya ver ve gözümün önünden kaybol!";
			link.l1.go = "barty_15";
			// belamour legendary edition -->
			link.l2 = "Mükemmel. Ve biliyor musun Sosa, fikrimi değiştirdim – artık Cizvit Tarikatı'na hizmet ediyorum. Kutsal Kitap'ta yazdığı gibi: 'Kötü kişiyi aranızdan çıkarın.' Sen ise aşağılık bir narsistsin, bir suçlu ve tamamen işe yaramaz bir pisliksin. Sanırım seni bu mağarada boğacağım. Requiesce in pace.";
			link.l2.go = "barty_15a";
		break;
		
		case "barty_15a":
			DialogExit();
			GiveItem2Character(pchar, "jewelry29");
			Log_Info("You received a turquoise ring");
			PlaySound("interface\important_item.wav");
			LAi_SetActorType(pchar);
			// если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			LAi_ActorAnimation(pchar, "Shot", "RIP_Sosa", 1.0); 
		break;
			
		case "barty_15":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			// <-- legendary edition
			GiveItem2Character(pchar, "jewelry29");
			Log_Info("You received a turquoise ring");
			PlaySound("interface\important_item.wav");
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", false);//офицеров пускать
			locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = false; //энкаутеры открыть
			locations[FindLocation("Cumana_Cave")].DisableEncounters = false; // patch
			LAi_LocationFightDisable(&Locations[FindLocation("Cumana_CaveEntrance")], false);//разрешить драться
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("GOT_Belinda");
			sld.dialog.currentnode = "Belinda_17";
			AddQuestRecord("Guardoftruth", "32");
		break;
		
		// охотники
		case "spa_hunter":
			dialog.text = "İhtiyacımız olan şey sende var...";
			link.l1 = "Gerçekten mi? Ve o neymiş bakalım?";
			link.l1.go = "spa_hunter_1";
		break;
		
		case "spa_hunter_1":
			dialog.text = "Sormadım, zengin çocuk. Bana emredildi, üzerindeki her şeyi, sahip olduğun ne varsa alacağım. Bunu kolay yoldan mı yapacağız, yoksa zor yoldan mı? Seçim senin.";
			link.l1 = "Kendini savaşçı mı sanıyorsun, ha? Kimle uğraştığını bilmiyorsun. Senin gibi pislikleri kahvaltıda yerim.";
			link.l1.go = "spa_hunter_2";
		break;
		
		case "spa_hunter_2":
			dialog.text = "Sen tam bir soytarısın, değil mi, kurbağa? O halde, bakalım kanın yerde nasıl duracak!";
			link.l1 = "Seninkiyle tıpatıp aynı olacak, aptal. Sana biraz anatomi dersi vereyim!";
			link.l1.go = "spa_hunter_3";
		break;
		
		case "spa_hunter_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i=1; i<=5; i++)
			{
				sld = characterFromID("GOT_santiagoband_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_SantiagoBandDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "cabin_hunter":
			dialog.text = "Haw haw, tamam dostum... Hadi, ceplerini hemen boşalt! Eğer uslu bir çocuk olup dinlersen, sağ salim kurtulursun, anladın mı?";
			link.l1 = "Lanet olsun, yine siz mi? Siz de buralara kadar mı geldiniz? Hangi şeytan tuttu sizi?!";
			link.l1.go = "cabin_hunter_1";
		break;
		
		case "cabin_hunter_1":
			dialog.text = "Bu seni ilgilendirmez. Şimdi teslim ol ve yaşa, ya da savaşmaya kalk ve ganimetini cesedinden alalım. Ne dersin, anlaşma böyle olsun mu?";
			link.l1 = "Sana bir karşı teklifim var. Ya ganimetini cesedinden alırsam?";
			link.l1.go = "cabin_hunter_2";
		break;
		
		case "cabin_hunter_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for(i=1; i<=2; i++)
			{
				sld = CharacterFromID("GOT_cabinband_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_CabinBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// командир абордажников
		case "batabano_officer":
			dialog.text = "Emirlerinizi bekliyorum, kaptan!";
			link.l1 = "San Antonio Burnu'na doğru ormanın içinden ilerleyin. Soldaki patikadan gidin ve dümdüz devam edin. Başınızı eğik tutun ve sahilde bir pusuya hazırlıklı olun. Hazır olun. Ben denizden geleceğim ve orada buluşacağız. Oraya varmanız ne kadar sürecek?";
			link.l1.go = "batabano_officer_1";
		break;
		
		case "batabano_officer_1":
			dialog.text = "Altı saat içinde orada olacağız, kaptan!";
			link.l1 = "Güzel. Hadi, hareket et!";
			link.l1.go = "batabano_officer_2";
		break;
		
		case "batabano_officer_2":
			DialogExit();
			LocatorReloadEnterDisable("Shore13", "boat", false);
			for(i=1; i<=10; i++)
			{
				sld = characterFromID("GuardOT_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 20.0);
			}
			AddQuestRecord("Guardoftruth", "48");
			// на мыс
			pchar.quest.GuardOT_sanantonio.win_condition.l1 = "Ship_location";
			pchar.quest.GuardOT_sanantonio.win_condition.l1.location = "Shore15";
			pchar.quest.GuardOT_sanantonio.function = "GuardOT_SanantonioArrive";
			// на время, специально для дебилов, не читающих диалоги и СЖ
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.hour  = sti(GetTime()+6);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.function = "GuardOT_SanAntonio_Timer";
		break;
		
		// наёмник Патерсона
		case "housemercen":
			dialog.text = "İnatçı herif! Hâlâ yaşıyor... Daha fazla barut kullanmamız gerektiğini biliyordum! Peki, tamam, işini bitireceğim, seni kahrolası herif...";
			link.l1 = "...";
			link.l1.go = "housemercen_1";
		break;
		
		case "housemercen_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			bDisableCharacterMenu = false;//разлочим F2
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			if (MOD_SKILL_ENEMY_RATE < 5) LAi_group_SetCheck("EnemyFight", "GuardOT_HouseMercenDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
