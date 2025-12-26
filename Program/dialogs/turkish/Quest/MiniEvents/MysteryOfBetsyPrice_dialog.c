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
			dialog.text = "Ne istiyorsun?";
			link.l1 = "Hiçbir şey.";
			link.l1.go = "exit";
		break;

		case "Poorman_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "Hey, güzelim, hanımefendinin koleksiyonuna eşsiz bir süs ister misin? Gerçek bir hazine! Sana hayran bakışlar, bana ise ekmek parasıyla bir yudum rom.";
			}
			else
			{
				dialog.text = "Hey, Kaptan, hanımınıza özel bir hediye ister misiniz? Gerçek bir hazine! Siz onun içten teşekkürünü alırsınız, ben de ekmekle bir yudum rom için birkaç akçe.";
			}
			link.l1 = "Bir saat sonra askerler gelip beni hırsızlıktan hapse atsın diye mi? Nereden buldun bunu, serseri?";
			link.l1.go = "Poorman_2_fortune";
			link.l2 = "Benzersiz bir hediye mi? Ve senin gibi bir evsiz, böyle bir şeyi nereden bulacakmış?";
			link.l2.go = "Poorman_2_leadership";
			if (npchar.quest.meeting == "0") npchar.quest.meeting = "1";
		break;

		case "Poorman_2_fortune":
			dialog.text = ""+GetSexPhrase("Kaptan, ben","Ben")+" Bu güzel bir kameo kolye buldum, vallahi doğruyu söylüyorum! Yalan söylüyorsam yerin dibine gireyim! Orada öylece, kimsenin umurunda olmadan duruyordu. Böyle bir güzelliği toprakta bırakabilir miydim, söyler misin?";
			link.l1 = "Pekala. Göster bakalım neyin var orada.";
			link.l1.go = "Poorman_3";
			link.l2 = "Böylesine saygın bir beyefendinin sözüne kim inanır ki? Git, daha saf birini bul.";
			link.l2.go = "Poorman_exit";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "Poorman_2_leadership":
			dialog.text = ""+GetSexPhrase("Kaptan, ben","Ben")+" Bu güzel bir madalyon buldum, üzerinde bir kabartma var, vallahi doğru söylüyorum! Yalan söylüyorsam yerin dibine gireyim! Öylece duruyordu, kimse istemiyordu. Böyle bir güzelliği toprağın içinde bırakabilir miydim, söyler misin?";
			link.l1 = "Pekala. Hadi, neyin var göster bakalım.";
			link.l1.go = "Poorman_3";
			link.l2 = "Böylesine saygın bir beyefendinin sözüne kim inanır ki? Git, daha saf birini bul.";
			link.l2.go = "Poorman_exit";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Poorman_exit":
			DialogExit();
			AddDialogExitQuestFunction("TBP_PismoVDome");
		break;
		
		case "Poorman_3":
			dialog.text = "Bak... bu gerçekten güzel bir şey! Onu fenerli evin yanındaki çiçeklikte, meyhanenin yakınında buldum. Ama orada uzun zamandır kimse yok, bu yüzden geri verecek kimse de yok.";
			link.l1 = "Merak uyandıran küçük bir süs eşyası. Peki, bunun için ne kadar istiyorsun?";
			link.l1.go = "Poorman_4";
		break;

		case "Poorman_4":
			dialog.text = "Sadece yüz peso"+GetSexPhrase(", Kaptan","")+"... senin gibi biri için kuruş bile değil! Ama benim için – bir hafta boyunca ekmek derdi olmadan yaşamak demek. Şuna bir bak – ne kadar güzel!";
			if (sti(pchar.Money) >= 100)
			{
				link.l1 = "Pekala, işte yüz peson.";
				link.l1.go = "Poorman_5";
			}
			link.l2 = "Bence ben almayayım. Şansını başkasıyla dene.";
			link.l2.go = "Poorman_exit";
		break;

		case "Poorman_5":
			dialog.text = "Teşekkür ederim, "+GetAddress_Form(NPChar)+"! Şimdi şansın kesinlikle senden yana olacak! İyi bir insansın, bu belli oluyor.";
			link.l1 = "...";
			link.l1.go = "Poorman_exit";
			GiveItem2Character(PChar, "jewelry24");
			pchar.questTemp.TBP_BuyKulon = true;
			pchar.questTemp.TBP_BuyKulonOtdatBetsy = true;
		break;
		
		case "Pirate_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "O-o-oh, kimler gelmiş bize? Görüyorum ki kapıyı yanlış çalmamışsın, tatlım... gir içeri, gir! Üstünü çıkar, rahatına bak.";
				link.l1 = "Vay vay... Bakalım burada kim varmış? Betsy'ye o 'nazik' tehdit mesajını bırakan alçaklar siz değil misiniz?";
			}
			else
			{
				dialog.text = "V-v-ve bu ne biçim mürekkepbalığı?! Yanlış kapıya mı geldin, keçi kafalı? Defol git buradan yoksa seni doğrarım!";
				link.l1 = "Vay vay... Burada kimleri görüyorum? Betsy'ye o güzel tehdit mesajını bırakan ahmaklar siz değil misiniz?";
			}
			link.l1.go = "Pirate_2";
		break;

		case "Pirate_2":
			if (pchar.sex == "woman")
			{
				dialog.text = "Betsy mi? O Betsy'nin canı cehenneme! Asıl ilginç olan senin burada ne yaptığın, güzelim... Madem buradasın – acele etmene gerek yok, seni oyalayacak bir yol buluruz...";
			}
			else
			{
				dialog.text = "Ne oluyor Betsy? Kaderi zorlama, aptal. Hâlâ kendi ayaklarınla çıkabiliyorken – çık. Yoksa seni parça parça toplayıp kovayla dışarı taşımak zorunda kalırız!";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_2");
		break;

		case "BetsiPrice_1":
			dialog.text = "Yardım edin! Ne olur, yardım edin!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_3");
			locCameraFromToPos(1.40, 1.62, 1.14, false, 2.58, -0.30, -1.64);
		break;
		
		case "Pirate_3":
			dialog.text = "...";
			link.l1 = "Ve işte orada. Başını belaya fena halde soktun dostum, ve bunun son hatan olmasını istemiyorsan, sana onu hemen serbest bırakmanı tavsiye ederim.";
			link.l1.go = "Pirate_4";
		break;

		case "Pirate_4":
			dialog.text = "Ha! Duydun mu bunu, Reggie? "+GetSexPhrase("O","O")+" hatta bizi tehdit ediyor. "+GetSexPhrase("Ne kadar kendini beğenmiş bir sümüklüböcek","Ne küstah saçmalık")+". Hey, hadi gösterelim "+GetSexPhrase("bu kendini bilmezin ciğerleri ne renkmiş görelim","bu kendini bilmez gerçek acının ne olduğunu görecek")+".";
			link.l1 = "Bu senin sonun.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_4");
		break;

		case "Pirate_5":
			if (!CharacterIsAlive("TBP_Bandit_1"))
			{
				dialog.text = "...";
				link.l1 = "Kızı şimdi bırak. Yoksa arkadaşının yanında yatarsın.";
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
			dialog.text = "Lanet olası köpekler! Sessiz kalacağımı mı sandınız?!";
			link.l1 = "...";
			link.l1.go = "BetsiPrice_2_1";
			sld = CharacterFromID("TBP_Bandit_2");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("TBP_BetsiPrice"));
			CharacterTurnByChr(npchar, sld);
		break;

		case "BetsiPrice_2_1":
			dialog.text = "Ve sen... Sen onlarla birlikte gibi görünmüyorsun. Kimsin sen?";
			link.l1 = "Kaptan "+GetFullName(pchar)+", hizmetinizde.";
			link.l1.go = "BetsiPrice_2_2";
			CharacterTurnByChr(npchar, pchar);
		break;

		case "BetsiPrice_2_2":
			dialog.text = "Yani, sana hayatımı borçlu muyum?";
			link.l1 = "Öyle görünüyor. Ama şimdi daha önemli bir şey var – bu insanlar kim ve sen neyin içine bulaştın?";
			link.l1.go = "BetsiPrice_3";
		break;
		
		case "BetsiPrice_3":
			dialog.text = "Bu insanlar... Onları önemli bir İngiliz yetkili gönderdi. Bir zamanlar bana çok yakındı... ve şimdi, gördüğün gibi, ölümümü istiyor.";
			link.l1 = "Hikayeni anlamaya başladığımı düşünüyorum. Onun metresiydin, ama bir noktada bunu kendi lehine kullanabileceğini düşündün. Onu korkutmak istedin... ailesine söylemek mi?";
			link.l1.go = "BetsiPrice_4";
		break;

		case "BetsiPrice_4":
			dialog.text = "Beklenmedik şekilde yakınsın"+GetSexPhrase("   gerçeğe, yakışıklı "," gerçeğe, tatlım")+"... ve aynı zamanda bundan çok uzakta. Eğer öyle olsaydı, şimdiye kadar çoktan ölmüş olurdum. Evet, onun metresiydim, ama aile dramaları çıkarmak hiç aklımdan geçmedi\nHer şey çok daha karmaşıktı: bir gün, kendine yeni bir oyuncak bulduğunu ve beni elinde hiçbir şey olmadan bırakmaya karar verdiğini öğrendim. Beni istenmeyen bir eşya gibi atıp kurtulmak istedi. Ama ben hiçbir şey almadan gitmeye alışık değilim\nBu yüzden gerçekten değerli olanı aldım – hayatını mahvedebilecek belgeleri – ve Yeni Dünya'ya kaçtım. Sonra da bir anlaşma teklif ettim: sırlarıma karşılık güvenliğim ve cömert bir ödeme\nİşte bu yüzden hâlâ hayattayım – belgeleri onlara lazım. Ve ben de onların nerede saklandığını açıklamak için hiç acele etmedim.";
			link.l1 = "Sen sadece güzel değil, aynı zamanda şeytani derecede kurnazsın. Cesurca oynadın, ama dürüst olalım – bu oyun artık senin kontrolünden çıktı. Belki de hâlâ bir şansın varken başka bir yol düşünmenin zamanı gelmiştir? Seni burada buldularsa, başka bir yerde saklanman pek mümkün görünmüyor. Er ya da geç şansın tükenecek.";
			link.l1.go = "BetsiPrice_5";
		break;

		case "BetsiPrice_5":
			dialog.text = "Ne öneriyorsun? Belgeleri ona verip elimiz boş mu kalalım? Bunca şeyden sonra mı?";
			link.l1 = "Onlar için sadece ortadan kaldırılması gereken bir sorundan ibaret olduğunu anlıyorsun, değil mi? İstediklerini alana kadar durmayacaklar. Ama hâlâ bir seçeneğin var. Şu köşedeki ahmağa belgeleri ver. O da onları efendisine iletsin ve senin niyetlerinden vazgeçtiğine, sadece bu işin bitmesini istediğine onu ikna etsin.";
			link.l1.go = "BetsiPrice_6";
		break;

		case "BetsiPrice_6":
			dialog.text = "Eğer bu benim tek şansım ise... Peki, riski göze almaya hazırım. Belgeleri her zaman yanımda tuttum. Onları korsetime diktim, bir an bile yanımdan ayırmamak için. Bir saniye, hemen...";
			link.l1 = "...";
			link.l1.go = "BetsiPrice_7";
		break;

		case "BetsiPrice_7":
			dialog.text = "Al bakalım. Bende olan bütün belgeler bunlar. O mahlûka birkaç veda sözü eder misin? İkna etmeyi bilirsin, değil mi?";
			link.l1 = "Bence ana dersi zaten öğrendi. Şimdi ona ne yapması gerektiğini açıkça anlatmamız gerekiyor.";
			link.l1.go = "exit";
			notification(StringFromKey("Neutral_15"), "BoxMinus");
			PlaySound("interface\\important_item.wav");
			AddDialogExitQuestFunction("TBP_HouseBetsi_11");
		break;
		
		case "Pirate_6":
			dialog.text = "...";
			link.l1 = "Kalk. Ve beni dikkatlice dinle, alçak. İşte almak için gönderildiğin belgeler. Bunları efendine götür ve ona şunu söyle: Betsy'nin peşine katil göndermeye devam ederse, onlar da arkadaşlarının akıbetini paylaşacak. Ona söyle, Betsy artık sonsuza dek hayatından çıkıyor – ve onu takip etmesi için hiçbir sebebi kalmadı. Bunu, Betsy'nin barış için attığı gönüllü bir adım olarak kabul etsin. Umarım bu işin burada bitmesi için yeterince akıllıca davranır. Her şeyi anladın mı, yoksa bu bilgileri kafana zorla mı sokmam gerekecek?";
			link.l1.go = "Pirate_7";
			notification(StringFromKey("Neutral_16"), "BoxMinus");
			PlaySound("interface\\important_item.wav");
		break;

		case "Pirate_7":
			dialog.text = "Her şeyi anladım, "+GetAddress_Form(NPChar)+"...";
			link.l1 = "O zaman defol git buradan. Ve sakın burada oyalanmayı düşünme – seni burada bir daha görürsem, ikinci bir şansın olmayacak.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_12");
		break;

		case "BetsiPrice_8":
			dialog.text = "Peki, "+GetSexPhrase("kahramanım","öfkem")+", galiba sana teşekkür etmeyi bile unuttum... Hep bu heyecandan. Her gün tutsak olup sonra böyle cesur birinin sayesinde özgürlüğünü geri kazanmaz insan "+GetSexPhrase("kurtarıcı","rescueress")+"  Söylesene, bu hanımları dertten kurtarmak senin alışkanlığın mı, yoksa ben mi inanılmaz şanslıyım?";
			link.l1 = "Ne diyebilirim Betsy, gösterişli girişlere karşı zaafım var ve "+GetSexPhrase("güzel hanımlar","her türlü macera")+".";
			link.l1.go = "BetsiPrice_9";
		break;

		case "BetsiPrice_9":
			dialog.text = "Benim adım Miranda. Miranda Bell. Kaybolmam gerektiğinde Betsy adını aldım – yeni hayat, yeni isim, anlarsınız ya. Avrupa’dan öyle aceleyle kaçtım ki, yanımda sadece birkaç bozukluk ve birkaç mücevher alabildim\nGeri kalan muhtemelen peşimdeki o alçaklara gitti. Şimdi ise lüks davetler ve pahalı kıyafetler yerine, şehrin kenarındaki sefil bir kulübe ve bir meyhanede çalışma var. Bir gün iyi bir sofrada şarap yudumlamak yerine başkalarına rom servis edeceğimi hiç düşünmezdim...";
			link.l1 = "Tüm bunlara rağmen, kaderin iplerini elinde tutuyormuşsun gibi görünüyorsun. Belki de asıl yeteneğin tam da burada yatıyor.";
			link.l1.go = "BetsiPrice_10";
		break;

		case "BetsiPrice_10":
			dialog.text = ""+GetSexPhrase("Yalaka. Ama biliyor musun, sana çok yakışıyor","Beni onurlandırıyorsun")+"... Bütün bunlardan sonra kendimi biraz huzursuz hissediyorum. Ya köşe başında beni bekliyorlarsa? Beni eve kadar götür, benim "+GetSexPhrase("kurtarıcı","savioress")+" biraz daha uzun süreliğine.";
			link.l1 = "Ben işleri yarım bırakmam. O yüzden, hanımefendi, emrinizdeyim. Hadi gidelim.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma");
		break;

		case "BetsiPrice_11":
			dialog.text = "İşte geldik. Biliyor musun, o eve hangi rüzgarla geldiğini bile sormadım?";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulonOtdatBetsy") && pchar.questTemp.TBP_BuyKulonOtdatBetsy == true)
            {
			link.l2 = "Orada tesadüfen bulunmadım. Bu kolye beni oraya getirdi. Al bunu.​ Meyhane sahibi kayboluşundan gerçekten endişelenmişti ve başına ne geldiğini öğrenmemi istedi. Eh, reddetme şansım var mıydı? Zor durumdaki bir kadını terk etmek bir kaptana yakışmaz.";
			link.l2.go = "BetsiPrice_12_otdal_kulon";
			}
			else
			{
			link.l1 = "Orada tesadüfen bulunmadım. Meyhane sahibi kayboluşunuza gerçekten üzülmüş görünüyordu ve başınıza ne geldiğini öğrenmemi istedi. Peki, reddetme şansım var mıydı? Zor durumda bir hanımefendiyi terk etmek bir kaptana yakışmaz.";
			link.l1.go = "BetsiPrice_12";
			}
		break;
		
		case "BetsiPrice_12":
			dialog.text = "Ah, bu gerçekten çok asilce, Kaptan "+pchar.name+"! Gerçi, eminim meyhaneci kârını düşünüyordu, beni değil. Ne yazık ki bugün seni içeri davet edemem – biraz toparlanmam gerek. Bodrumda geçirdiğim zaman güzelliğime güzellik katmadı doğrusu. Ama bir daha görüşmezsek – bunu sana asla affetmem. O yüzden yarın meyhaneye gel, sana bir... hediyem olacak.";
			link.l1 = "Eh, şimdi uğramak için bir sebebim daha var. Görüşürüz, M... Betsy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_3");
		break;
		
		case "BetsiPrice_12_otdal_kulon":
			dialog.text = "Ah, bu çok asilce, Kaptan "+pchar.name+"! Gerçi, eminim meyhaneci benimle değil, kârıyla daha çok ilgileniyordu. Ne yazık ki bugün seni içeri davet edemem – biraz toparlanmam lazım. Bodrumda geçirdiğim zaman beni güzelleştirmedi doğrusu. Ama bir daha görüşmezsek – bunu sana asla affetmem. Yarın meyhaneye mutlaka gel, sana bir... hediyem olacak.";
			link.l1 = "Eh, şimdi uğramak için bir sebebim daha var. Görüşürüz, M... Betsy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_3");
			TakeItemFromCharacter(pchar, "jewelry24");
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
		break;

		case "TBP_Helena_1":
			dialog.text = "Vay vay... Ne hoş bir veda. Kim bu dağınık hanımefendi? Bir haftadır bodrumda oturuyormuş gibi görünüyor, ama bu bile onu gözlerinle yutmana engel olamamış, değil mi, "+pchar.name+"?";
			link.l1 = "Sandığın gibi değil. Kız kendini zor bir durumda buldu, ben de ona çıkmasına yardım ettim. Hepsi bu.";
			link.l1.go = "TBP_Helena_2";
		break;

		case "TBP_Helena_2":
			dialog.text = "Ve tabii ki, onun için parlayan zırhlı şövalye olmaya karar verdin, değil mi?";
			link.l1 = "Biliyor musun, birisi tehlikedeyken kenarda duramam.";
			link.l1.go = "TBP_Helena_3";
		break;

		case "TBP_Helena_3":
			dialog.text = "Peki. Ama bir dahaki sefere, "+pchar.name+", biraz daha dikkatli ol... ve bana kıskanmam için sebep verme.";
			link.l1 = "Elbette, sevgilim. Hadi buradan çıkalım, hâlâ yapacak çok işimiz var.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_5");
		break;

		case "TBP_Mary_1":
			dialog.text = "Vay vay... Ne tatlı bir veda. Ne kadar özenli, ne kadar içten sözler... Bir de adını böyle sevgiyle söylüyorsun, peki. Belki ben de birkaç gün ortadan kaybolsam, beni de aynı hevesle ararsın?";
			link.l1 = "Mary, biliyorsun sen benim tılsımım oldun, o ise... sadece başını belaya sokmuş bir kız.";
			link.l1.go = "TBP_Mary_2";
		break;

		case "TBP_Mary_2":
			dialog.text = "Ah, tabii! Zavallı bir kızcağız, bir şövalyeye muhtaç! Ve o bakışın – o da mı sadece kibarlıktandı? Az kalsın gözlerinle üstünü başını soyacaktın!";
			link.l1 = "Mary, abartıyorsun! Sana nasıl baktığıma bir bak. Farkı görüyor musun? Yoksa sana... yakından mı hatırlatmam gerekecek?";
			link.l1.go = "TBP_Mary_3";
		break;

		case "TBP_Mary_3":
			dialog.text = "Pekâlâ, "+pchar.name+", bu sefer paçayı kurtardın, tamam mı. Ama böyle bir sahneye bir daha rastlarsam...";
			link.l1 = "O zaman sana bir kez daha hatırlatmam gerekecek, kalbimdeki ilk ve tek yerin sahibi kim. Hadi sevgilim, daha yapacak çok işimiz var.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_5");
		break;
		
		case "BetsiPrice_sex_1":

			switch (rand(1))
			{
				case 0:
					dialog.text = "Mmm... Sana bu kadar yakınken aklımdan geçenleri hayal bile edemezsin... Ve onları gerçeğe dönüştürmeyi ne kadar çok istediğimi.";
					link.l1 = "O zaman sadece düşünmekle kalma... ve bana hepsini tek tek göster.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "Ah, sevgilim"+GetSexPhrase("","")+"... sen yanımdayken kendimi kontrol etmek benim için ne kadar zor, bilemezsin...";
					link.l1 = "O halde bu tatlı işkence yeter... Gel bana...";
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
					dialog.text = "Ah, "+GetSexPhrase("tatlı kaptanım","tatlım "+pchar.name+"")+"... Hâlâ bu tatlı deliliğin içinde sıkışıp kaldım.";
					link.l1 = "Belki de bu delilik hatırlanmaya değer... ya da bir gün yeniden yaşanmaya.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "Oh, "+pchar.name+"...   Eğer harikaydı dersem, fazla gururlanmazsın umarım "+GetSexPhrase(", yapar mısın?",". yapacak mısın?")+"?";
					link.l1 = "Sadece tekrar söyleyeceğine söz verirsen... fısıltıyla.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
			AddDialogExitQuestFunction("TBP_Betsi_sex_7");
		break;

		
		
		
		
		
		
		
	}
}