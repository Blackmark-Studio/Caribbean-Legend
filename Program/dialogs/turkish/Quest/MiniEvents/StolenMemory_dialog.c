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

		case "Juli":
			dialog.text = "...";
			if (pchar.sex == "woman")
			{
				link.l1 = "Matmazel, Port-au-Prince'in cazibesinin sizin gülüşünüz olmadan kaybolduğunu söylerler. Görünen o ki, bugün o günlerden biri. Açıklığımdan dolayı affedin, ama sizi üzen bir şey mi var?";
			}
			else
			{
				link.l1 = "Madam, güzelliğiniz ve zarafetinizle ilgili hikâyeler kulağıma kadar geldi, ama itiraf etmeliyim ki—söylentiler sizi tarif etmekte yetersiz kalıyor. Ayrıca derler ki, siz gülmediğinizde Port-au-Prince de tüm cazibesini kaybedermiş. Ne yazık ki, bugün de öyle bir gün gibi görünüyor. Kim o alçak, keyfinizi kaçırmaya cüret eden? İsmini söyleyin, onurunuz için onunla düello etmeye yemin ederim; yüzünüzdeki o güzel gülümsemeyi geri getireceğim.";
			}
			link.l1.go = "Juli_2";
			DelLandQuestMark(npchar);
		break;

		case "Juli_2":
			if (pchar.sex == "woman")
			{
				dialog.text = "Ah, mademoiselle, ilginiz gerçekten dokunaklı... İtiraf etmeliyim ki, endişeniz beni etkiledi. Ama ne yazık ki, kederimin sebebi sadece bir sohbetle dağıtılacak türden değil. Bu, herhangi birinin suçu değil; korkarım ki, en kararlı olanların bile aşamayacağı koşulların bir sonucu.";
				link.l1 = "Koşullar mı? Emin olun, mademoiselle, çünkü "+GetFullName(pchar)+" hiçbir engel aşılamaz değildir. Ne olduğunu anlat—belki yardımcı olabilirim.";
			}
			else
			{
				dialog.text = "Ah, monsieur, gerçekten de güzel sözlerin ustasısınız. İtiraf etmeliyim ki, neredeyse yüzümde bir tebessüm bırakmayı başardınız. Ama ne yazık ki, bir düello benim derdime çare olmaz. Günümü karartan biri değil, sizin gibi centilmen birinin bile aşamayacağı talihsiz koşullar.";
				link.l1 = "Durumlar mı? Sevgili mademoiselle, Kaptan "+GetFullName(pchar)+" her fırtınaya göğüs gerebilirim! Ve eğer başarısız olursam, sana yemin ederim, karşıma çıkan ilk kişinin şapkasını yiyeceğim!";
			}
			link.l1.go = "Juli_3";
		break;

		case "Juli_3":
			if (pchar.sex == "woman")
			{
				dialog.text = "Eğer gerçekten ısrar ediyorsanız, size ne olduğunu anlatacağım. Ama önce, bu konuşmanın aramızda kalacağına dair sözünüze ihtiyacım var.";
				link.l1 = "Sana namusum ve şerefim üzerine söz veriyorum, mademoiselle. Bana ne anlatırsan anlat, aramızda kalacak; gerekirse bu sırrı okyanusun derinliklerine bile götürürüm.";
			}
			else
			{
				dialog.text = "Monsieur "+pchar.lastname+", gerçekten de en dertli hanımefendinin bile yüzünü güldürebilecek bir yeteneğiniz var. Ama lütfen, masum geçenlerin şapkalarına acıyın. Eğer gerçekten ısrar ediyorsanız, başıma gelenleri anlatacağım. Yalnızca söz verin, anlattıklarım aramızda sır olarak kalsın.";
				link.l1 = "Söz veriyorum, mademoiselle, bana söylediğiniz her şey mutlak gizlilik içinde kalacak, ölüm tehdidi altında bile.";
			}
			link.l1.go = "Juli_4";
		break;
		
		case "Juli_4":
			dialog.text = "Pekâlâ. Odalarımdan bir kolye kayboldu... ama bilmelisiniz ki, bu sıradan bir süs eşyasından çok daha fazlası. O kolye bana kalbimde çok özel bir yeri olan biri tarafından verilmişti. Yokluğu, bir eşyanın kaybından çok daha derin bir yara gibi hissettiriyor\nUzun uzun düşündüm, kimin sorumlu olabileceğini. Ve tek bir sonuca varabildim. Korkarım, suçlu hizmetkârlarımdan biri olmalı. Sadece onların özel odama girmeye izni var ve böylesine değerli bir parçaya göz koymuş olabilirler. Yine de, bu suçlamayı açıkça dile getirmeye cesaret edemem...";
			link.l1 = "Gerçekten de son derece hassas bir mesele, özellikle de gizlilik istiyorsanız. Ama size yardım edebilmem için, bu sırrı neden bu kadar titizlikle sakladığınızı anlamam gerek. Karşı karşıya olduğumuz tehlikeleri bilmeden, ikimizi de farkında olmadan belaya sürükleyebilirim. Kimden uzak durmamız gerektiğini ve gölgelerde hangi tehditlerin saklandığını bana anlatın.";
			link.l1.go = "Juli_5";
			if (pchar.sex == "woman")
			{
				link.l2 = "Özgürce konuşamıyor musunuz? O halde korkarım ki size iyi dileklerimden fazlasını sunamam, mademoiselle. Entrika ve gizlilik bana göre değil, ne hevesim var ne de yeteneğim. Bana kalırsa, kasaba muhafızlarının yardımıyla sorununuz hızla çözülebilir. Ama anlaşılan siz, bu çalkantılı sularda daha tehlikeli bir yol seçmişsiniz.";
				link.l2.go = "Juli_end";
			}
			else
			{
				link.l2 = "Açıkça konuşamıyor musunuz? O halde sizi affetmemi rica etmeliyim, mademoiselle, çünkü bu gizem perdesi içinde kendimi tamamen çaresiz hissediyorum. Gizli işlerden ve gölgeli anlaşmalardan pek hoşlanmam. Sizin sıkıntınız bana oldukça basit görünüyor: kasaba muhafızlarının kolayca çözebileceği bir mesele. Ama siz bunu, sanki Avrupa'nın kraliyet saraylarına layık bir entrika haline getirmeye kararlı gibisiniz.";
				link.l2.go = "Juli_end";
			}
		break;

		case "Juli_end":
			dialog.text = "Ünlü Kaptan böyle mi davranır "+GetFullName(pchar)+" zorlukla mı karşılaşıyorsunuz? İlk karmaşıklık belirtisinde geri çekilerek mi? Belki de yetenekleriniz rom fıçılarını saymakta ya da limandaki tüccarlarla laf dalaşı yapmakta daha iyi işe yarar. Sadece şunu istiyorum: Eğer içinde zerre kadar onur varsa, paylaştıklarımı en sıkı gizlilikle sakla. İyi günler dilerim, Kaptan.";
			link.l1 = "...";
			link.l1.go = "Juli_end_2";
		break;
		
		case "Juli_end_2":
			DialogExit();
			CloseQuestHeader("UV");
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "Juli_5":
			dialog.text = "Akıllıca konuşuyorsun, "+GetAddress_Form(NPChar)+". Gerçek şu ki, bu kolye amcamın öfkesini üzerine çeken bir adamdan geldi—bu adadaki Fransız topraklarının valisinden. Amcam onunla her türlü teması, hatta adının anılmasını bile yasakladı. Eğer amcam bu hediyenin nereden geldiğini öğrenirse, sonuçları yalnızca benim için değil, aynı zamanda...";
			link.l1 = "Daha fazla bir şey söylemeyin, mademoiselle. Sizi tamamen anlıyorum. İçiniz rahat olsun, kolyenizi en büyük gizlilikle bulacağım ve sırrınızı bir ejderha hazinesini korur gibi koruyacağım.";
			link.l1.go = "Juli_6";
		break;

		case "Juli_6":
			dialog.text = "En derin şükranlarımı sunarım, "+GetSexPhrase("Monsieur "+pchar.lastname+"",""+pchar.name+"")+" Cesur ve anlayışlı tavrınız, bu zor zamanlarda kalbimi ısıtıyor. Sırrımın sizinle güvende olduğuna yürekten inanıyorum. Bu hassas yolculukta talihin rüzgarları yelkenlerinizi doldursun.";
			if (pchar.sex == "woman")
			{
				link.l1 = "Şans, harekete geçmeye cesaret edenleri kucaklar, madam. İçiniz rahat olsun—kolyenizi mutlaka bulacağım, tıpkı gelgitin kıyıya dönmesi gibi.";
			}
			else
			{
				link.l1 = "Şans cesur olanların yanında, madam. Kıymetli kolyenizi bulduğum anda, hak ettiği yere, o zarif ellerinize geri dönecek.";
			}
			link.l1.go = "Juli_7";
		break;

		case "Juli_7":
			DialogExit();
			
			NextDiag.CurrentNode = "Juli_7_again";
			AddQuestRecord("UV", "2");
			AddQuestUserData("UV", "sSex", GetSexPhrase("","а"));
			
			pchar.questTemp.UV_Lavochniki = true;
		break;

		case "Juli_7_again":
			if (CheckCharacterItem(PChar, "SM_necklace_Julie"))
			{
				dialog.text = "Ah, Kaptan, geri döndünüz! Bana bir haberiniz var mı? Lütfen kolyemi bulduğunuzu söyleyin. Ne olur, öyle deyin.";
				link.l1 = "Sorunların sona erdi, Julie. Kolye bulundu ve onu hak ettiği yere, yani narin ellerine geri vermek bana büyük bir mutluluk veriyor.";
				link.l1.go = "Juli_22";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Ah, Kaptan, döndünüz! Bana bir haberiniz var mı? Lütfen kolyemi bulduğunuzu söyleyin. Ne olur, öyle deyin.";
				link.l1 = "Seni hayal kırıklığına uğrattığım için üzgünüm, Julie. Arayış devam ediyor. Ama üzülme—o değerli kolyeni sana geri kazandırana kadar hiçbir taşı yerinde bırakmayacağım.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Juli_7_again";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "Starpom_1":
			dialog.text = "Selamlar, efendim. Hangi iş sizi gemimize getirdi?";
			link.l1 = "I seek Captain Tristan Renier; I come bearing a proposition that would line his pockets handsomely.";
			link.l1.go = "Starpom_2_sneak";
			link.l2 = "Kaptan Tristan Renier ile biraz hassas bir konuda konuşmam gerek—kişisel bir mesele, anlıyorsunuz.";
			link.l2.go = "Starpom_2_fortune";
			DelLandQuestMark(npchar);
		break;

		case "Starpom_2_sneak":
			dialog.text = "Kaptan karaya çıktı, korkarım. İşiniz acilse onu kasabada bir yerde bulabilirsiniz.";
			link.l1 = "Varış yerini biliyor musunuz? Bu limana geldiğinde özellikle uğradığı bir yer var mı?";
			link.l1.go = "Starpom_3";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "Starpom_2_fortune":
			dialog.text = "Kaptan maalesef karaya çıktı. Eğer işiniz acilse, onu kasabada bir yerde bulabilirsiniz.";
			link.l1 = "Varış yerini biliyor musunuz? Bu limana geldiğinde özellikle uğradığı bir yer var mı?";
			link.l1.go = "Starpom_3";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "Starpom_3":
			dialog.text = "Özür dilerim, "+GetAddress_Form(NPChar)+", ama kaptan nereye gidip geldiğini kimseyle paylaşmaz. Bildiğim tek şey, birkaç saat önce karaya çıktığı.";
			link.l1 = "Bu kadarı bile yardımcı oldu. Yardımınız için teşekkür ederim.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_GoldSeagull_RasprashivaemZhiteley");
		break;

		case "Captain_1":
			if (pchar.sex == "man")
			{
				dialog.text = "Sen de kimsin? Hangi hakla izinsiz olarak özel odama girmeye cüret ediyorsun?";
				link.l1 = "Ben Kaptanım "+GetFullName(pchar)+". Ve önemli bir mesele için geldim.";
			}
			else
			{
				dialog.text = "Ve siz kimsiniz, hanımefendi? Bu akşam davetiye gönderdiğimi hatırlamıyorum. Ama itiraf etmeliyim ki, bazı beklenmedik misafirler diğerlerinden daha... ilgi çekici olabiliyor. Böyle bir güzelliği mütevazı odama getiren sebep nedir?";
				link.l1 = "Ben Kaptanım "+GetFullName(pchar)+".   Ziyaretim iş için, eğlence için değil.";
			}
			link.l1.go = "Captain_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Captain_2":
			if (pchar.sex == "man")
			{
				dialog.text = "İş mi, öyle mi? Ne tür bir mesele böylesine kaba bir şekilde rahatsız etmeye değer olabilir?";
				link.l1 = "Oldukça basit. Benim almaya geldiğim bir kolyeye sahipsiniz.";
			}
			else
			{
				dialog.text = "İş, diyorsunuz? Ne kadar ilginç... Sizi, böylesine etkileyici bir hanımefendiyi, özel odama kadar getiren acil ticari mesele nedir acaba?";
				link.l1 = "Bana tatlı sözler söyleme, monsieur. Senin elindeki kolyeyi almaya geldim. Ve evet, onu tam olarak sende olduğunu biliyorum.";
			}
			link.l1.go = "Captain_3";
		break;

		case "Captain_3":
			if (pchar.sex == "man")
			{
				dialog.text = "Ha! Bir kolye mi diyorsun? Gerçekten de yakın zamanda böyle bir parça edindim, ama bu seni neden ilgilendiriyor? Herhalde ilk karşıma çıkan yabancı isteyince malımı hemen teslim edeceğimi sanmıyorsun?";
			}
			else
			{
				dialog.text = "Bir kolye mi? Doğrusu... Yakın zamanda böyle bir takı edindim. Ama söyle bakalım kaptan, bana ait olan bu mücevheri benden nasıl almayı düşünüyorsun?";
			}
			if (sti(pchar.Money) >= 5000)
			{
				link.l1 = "Sana bu parça için beş bin peso teklif etmeye hazırım. Bu, sana en az onun kadar güzel, belki de daha gösterişli bir süs eşyası almana yetecek kadar cömert bir meblağ. Öte yandan, bu özel kolye, değeri parayla ölçülemeyecek kadar kıymet veren asıl sahibine kavuşmuş olacak.";
				link.l1.go = "Captain_4_commerce";
			}
			link.l2 = "Açık konuşayım, efendim. Seçenekleriniz oldukça azaldı: Kolye'yi isteyerek teslim edin ve bir başka gün yelken açmaya devam edin, ya da karşı koyun ve onu cansız bedeninizden almamı sağlayın. Karar sizin, fakat hızlı olmanızı tavsiye ederim.";
			link.l2.go = "Captain_4_leadership";
		break;

		case "Captain_4_commerce":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 25)
			{
				dialog.text = "Beş bin mi diyorsunuz? Peki o zaman, Kaptan, pazarlıkta ustasınız. Alın şu süsü, madem bu kadar önemsiyorsunuz.";
				link.l1 = "Hikmetiniz cömertliğinizle yarışıyor, efendim. Bu karardan pişman olmayacaksınız.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie");
				Notification_Skill(true, 25, SKILL_COMMERCE);
				GiveItem2Character(pchar, "SM_necklace_Julie");
				ChangeCharacterComplexReputation(pchar, "nobility", 2);
				AddMoneyToCharacter(pchar, -5000);
			}
			else
			{
				dialog.text = "Bu kolyeyi ilk karşıma çıkan serseriye birkaç kuruş karşılığında vermek için almadım! O, eşime hediye olarak düşünüldü ve bu konuda daha fazla konuşmak istemiyorum. Şimdi önümden çekil yoksa adamlarımı çağırıp seni dışarı attırırım!";
				link.l1 = "Eğer bir centilmen anlaşmasını reddederseniz, aradığımı daha az medeni yollarla elde edeceğim.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie_Duel");
				Notification_Skill(false, 25, SKILL_COMMERCE);
			}
		break;
		
		case "Captain_4_leadership":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 45)
			{
				dialog.text = "Argh... Seni küstah velet... Çocuksu tehditlerinle beni korkutacağını mı sanıyorsun? Ha! Kiminle uğraştığını hiç bilmiyorsun!";
				link.l1 = "Kim olduğunu umursamıyorum. Kolyeyi ver, gideyim. Yoksa senin için hiçbir anlamı olmayan bir süs eşyası uğruna ölmeye gerçekten razı mısın?";
				link.l1.go = "Captain_4_leadership_2";
				notification("Check passed", SKILL_Leadership);
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
			else
			{
				dialog.text = "Bu kolyeyi senin gibi biriyle pazarlık yapmak için almadım! O, karıma bir hediyeydi ve burada işin yok. Defol git, yoksa seni biz atarız!";
				link.l1 = "Eğer onu huzur içinde vermezsen, zorla alırım.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie_Duel");
				notification("Skill not high enough (45)", SKILL_Leadership);
			}
		break;

		case "Captain_4_leadership_2":
			dialog.text = "Lanet olsun sana ve o uğursuz kolyeye! Al şunu. Al ve defol git, yoksa fikrimi değiştiririm.";
			link.l1 = "Akıllıca bir karar! Hoşça kal.";
			AddDialogExitQuestFunction("UV_Ozherelie");
			GiveItem2Character(pchar, "SM_necklace_Julie");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;

		case "Juli_22":
			dialog.text = ""+pchar.name+", kalbime yeniden sevinç getirdin! Sadece kolyemi değil, ruhumun bir parçasını da geri verdin. Asaletin gerçekten takdire şayan, ve cesaretini herkese anlatacağıma söz veriyorum!";
			link.l1 = "Lütfen, mademoiselle, onu şöhret için geri getirmedim. Gerçekten değer verdiğim tek ödül sizin gülümsemeniz.";
			link.l1.go = "Juli_23";
			TakeItemFromCharacter(pchar, "SM_necklace_Julie");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;

		case "Juli_23":
			dialog.text = "Ne kadar mütevazısın, "+pchar.name+". Ama lütfen, bu sandık dolusu dublonu kabul edin. Sadece hediyemi kabul ettiğinizi bilmek, size gerçekten hak ettiğiniz gibi teşekkür ettiğimi hissettirecek.";
			link.l1 = "Lütfen, mademoiselle, ısrar etmeyin. Güzel sözleriniz benim için bir sandık altından daha değerli.";
			link.l1.go = "Juli_24_nobility";
			link.l2 = "Eğer bu sizi rahatlatacaksa, mademoiselle, hediyenizi kabul edeceğim. Ama bilin ki bunu bir ödül için yapmadım. "+GetSexPhrase("Tanınırlığın"," Minnettarlığınız ")+" bu doblonlardan çok daha fazla anlam ifade ediyor.";
			link.l2.go = "Juli_24_chest";
		break;
		
		case "Juli_24_nobility":
			dialog.text = "Tamamen sormayı unuttum—kolyeyi kimin çaldığını biliyor musun?";
			link.l1 = "Tek bildiğim, mademoiselle, bir tüccarın onu Giselle adında birinden aldığı. Ve şartlara bakılırsa, bu onun satmayı planladığı son mücevher olmayabilir.";
			link.l1.go = "Juli_25";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;

		case "Juli_24_chest":
			dialog.text = "Az kalsın sormayı unutuyordum—kolyeyi kimin çaldığını biliyor musun?";
			link.l1 = "Tek bildiğim, mademoiselle, bir tüccarın bunu Giselle adında birinden aldığı. Ve gördüğüm kadarıyla, bu satacağı son mücevher olmayabilir.";
			link.l1.go = "Juli_25";
			GiveItem2Character(PChar, "chest");
		break;

		case "Juli_25":
			dialog.text = "Giselle mi? Ama o benim hizmetçim! Şüphelerim vardı... ama inanmak istemedim. En kötüsü de, onu doğru düzgün cezalandıramam bile. Sırrımı ortaya çıkarabilir—buna asla izin veremem.";
			link.l1 = "Peki şimdi ne yapacaksın? Onun bu yaptıklarına göz yumup seni soymaya devam etmesine izin mi vereceksin?";
			link.l1.go = "Juli_26";
		break;

		case "Juli_26":
			dialog.text = "Ah, hayır, tabii ki değil. Önce onun artık yakınımda olmadığından emin olacağım. Sonra da cezayı başka bir yerden gelmiş gibi gösterecek bir yol bulacağım.";
			link.l1 = "Bir kadının kurnazlığı tehlikeli bir silahtır, özellikle de sizin kadar zarif ve sezgili birinin ellerindeyse. Eminim hizmetçiniz oyunun çoktan kaybedildiğinin farkında bile değil—hem de kendi lehine değil.";
			link.l1.go = "Juli_27";
		break;

		case "Juli_27":
			dialog.text = "Ah, kaptan... Hileye başvurmak istemem ama... bazen kurnazlık tek çıkar yol olur.";
			link.l1 = "Gerçekten de, Julie. Senden ayrılmaktan nefret ediyorum ama görev beni çağırıyor. Mürettebatıma benden başka kim göz kulak olacak?";
			link.l1.go = "Juli_28";
		break;

		case "Juli_28":
			dialog.text = "Tekrar görüşene dek, "+pchar.name+" . Limanımıza daha sık uğrayın lütfen. Şehrimizde gerçekten eksik olan bir şey var "+GetSexPhrase("sizin gibi asil ve cesur adamlar.","seninki gibi asil bir kalbe ve cesur bir ruha sahip hanımlar.")+"";
			link.l1 = "Beni onurlandırıyorsunuz, madam. Söz veriyorum, güzel şehrinize dönmek için hiçbir fırsatı kaçırmayacağım. Bir dahaki sefere kadar.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_Juli_GoodEnd");
		break;
		
		case "Juli_31":	
			if (CheckAttribute(pchar, "questTemp.UV_ojerelie_Julie"))
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = ""+pchar.name+"! Ne sürpriz! Hâlâ denizleri fethediyor musun?";
						link.l1 = "Sizi görmek güzel, madam. Elimden geldiğince fethetmeye çalışıyorum, ama deniz hâlâ affetmez bir şekilde huysuz. Peki ya siz—biraz huzur ve sessizliğin tadını çıkarıyor musunuz?";
						link.l1.go = "Juli_32";
					break;

					case 1:
						dialog.text = "Ah, Kaptan "+pchar.lastname+", seni tekrar görmek ne güzel! Umarım her şey yolundadır?";
						link.l1 = "Sizi görmek de benim için büyük bir mutluluk, madam. İşler her zamanki gibi zaman ve emek istiyor ama böyle buluşmalar günü aydınlatıyor. Peki sizin günleriniz nasıl geçti?";
						link.l1.go = "Juli_33";
					break;
				}
			}
			else
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Kaptan "+pchar.lastname+", yine mi geldin? Bizim mütevazı kasabamızda hâlâ bir avuç altın için ihanet etmediğin insanlar mı kaldı gerçekten?";
						link.l1 = "Madam, duygularınızı anlıyorum, ama doğru olduğuna inandığım şekilde davrandım. Bazen doğru karar acı verir ve sizi incittiğim için üzgünüm.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Juli_34_zlaya";
					break;

					case 1:
						dialog.text = "Kaptan "+pchar.lastname+" , yine mi? Açgözlülüğün o kadar mı sınırsız ki kasabamızı rahat bırakmıyor, bir sonraki kurbanını mı arıyorsun?";
						link.l1 = "Madam, yaptıklarımla size acı verdiğim için üzgünüm, ama vicdanıma göre davrandım.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Juli_34_zlaya";
					break;
				}
			}
			SetTimerFunction("UV_Julie_HelloAgain", 0, 0, 1);
		break;

		case "Juli_32":	
			dialog.text = "Son zamanlarda her şey sakin ve huzurlu—hiçbir şey bu huzuru bozmuyor. Limanımıza daha sık uğrayın, Kaptan. Eminim burada, hem dükkânımızda hem de dışında, aradığınız her şeyi bulacaksınız.";
			link.l1 = "Teşekkür ederim, madam. Daha sık uğramaya çalışacağım. Eminim kasabanızda hâlâ birçok hoş sürpriz vardır.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Juli_repeat_residence_1";
		break;
		
		case "Juli_33":	
			dialog.text = "Sayende, kaptan, artık günlerim çok daha huzurlu. Umarım yine bizi ziyaret edersiniz.";
			link.l1 = "Elbette, mademoiselle. Kasabanız her zaman en hoş izlenimi bırakıyor. Bir dahaki sefere kadar.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Juli_repeat_residence_1";
		break;

		case "Juli_repeat_residence_1":
			switch (rand(1))
			{
				case 0:
					dialog.text = "Kaptan "+pchar.lastname+", yine karşılaştık. Ne kadar da ilginç, değil mi?";
					link.l1 = "Bugün karşılaşmalarımızda kader bize gülümsüyor gibi görünüyor, madam.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_repeat_residence_1";
				break;

				case 1:
					dialog.text = "Kaptan "+pchar.lastname+", yollarımız bir kez daha kesişmiş gibi görünüyor.";
					link.l1 = "Gerçekten de öyle, madam. Sizi tekrar görmek güzel.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_repeat_residence_1";
				break;
			}
		break;

		case "Juli_34_zlaya":
			switch (rand(1))
			{
				case 0:
					dialog.text = "Galiba biraz fazla sık karşılaşıyoruz, kaptan. Yoksa bir kez ihanete uğrattıklarından uzak duramıyor musun?";
					link.l1 = "Matmazel, karşılaşmalarımız tamamen tesadüf, ama öfkenizi anlıyorum. Sadece bir gün benim nedenlerimi de anlayacağınızı umuyorum.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_34_zlaya";
				break;

				case 1:
					dialog.text = "Şimdi ne istiyorsun? Şansın bu kadar kötü olamaz, bunun tesadüf olduğunu söyleme bana. Yoksa sadece rezaletini bana hatırlatmaya mı geldin?";
					link.l1 = "Hanımefendi, sizi rahatsız etmek ya da eski yaraları deşmek gibi bir niyetim yoktu. Bu karşılaşma gerçekten tesadüf.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_34_zlaya";
				break;
			}
		break;

		
		
		
		
		
		
		
	}
}