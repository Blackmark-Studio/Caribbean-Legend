// отец Винсенто
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "santiago")
			{
				dialog.text = "마침내, 명성 높은 프랑스 선장을 보게 되는군 "+GetFullName(pchar)+" 직접 만나게 되었군. 자네의 무용담은 많이 들었네. 자네는 용감한 군인이자, 바라건대 우리 어머니이신 로마 가톨릭 교회의 충직하고 신실한 아들이길 바라네. 앉게, 아들아. 내 앞이라고 굳이 서 있을 필요 없네. 도미누스 보비스쿰! ";
				link.l1 = "Et cum spiritu tuo, 각하. 이곳까지 오는 길이 길고도 험난했나이다... Per aspera ad astra, 뭐 그런 것이지요...";
				link.l1.go = "utensil";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "twoitems" && !CheckAttribute(npchar, "quest.skinmap"))
			{
				dialog.text = "그래, 네 눈을 보니 나에게 전할 소식이 있군. 전적으로 귀 기울이고 있네.";
				link.l1 = "각하, 잃어버린 비서를 찾았습니다...";
				link.l1.go = "guardoftruth";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "mayak")
			{
				dialog.text = "산호세에서 소식을 가져왔느냐, 아들아?";
				link.l1 = "예, 각하. 저희의 공통 지인 미겔 디초소와 그의 실종된 프리깃함에 무슨 일이 있었는지 알아냈습니다. 그의 배가 스페인으로 향해 대서양에 들어서자마자, 즉시 역풍을 만나 카리브 해로 다시 휘말려 돌아왔습니다.";
				link.l1.go = "guardoftruth_10";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "begin")
			{
				dialog.text = "평화가 함께하길, 아들아... 무엇을 도와줄까?";
				link.l1 = TimeGreeting()+", 각하. 우리 합의에 관한 소식이 있으십니까?"link.l1.go ="guardoftruth_17";
				break;
			}
			dialog.text = "무슨 볼일이 있느냐, 아들아?";
			link.l1 = "아니에요, 아무것도 아니에요, 아버지.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "utensil":
			dialog.text = "'좁은 문으로 들어가라; 멸망으로 인도하는 문은 크고 그 길이 넓어 그리로 들어가는 이가 많으니라. 생명으로 인도하는 문은 좁고 길이 협착하여 찾는 이가 적으니라.' \n의로운 길은 언제나 험난하단다, 아들아. 그러나 그 목표를 이루면, 의로운 자는 자신의 행위에 대해 충분한 보상을 받게 된다.";
			link.l1 = "동의합니다, 각하. 맡기신 임무들을 모두 완수하였습니다. 교회의 귀중한 성물을 훔친 비겁한 해적도 이미 잡으셨지요. 이제 빼앗겼던 모든 물건, 즉 성광과 십자가, 그리고 향로를 모두 돌려드립니다. 산티아고 본당을 위해 받아주십시오.";
			link.l1.go = "utensil_1";
		break;
		
		case "utensil_1":
			RemoveItems(pchar, "jewelry33", 1);
			RemoveItems(pchar, "jewelry34", 1);
			RemoveItems(pchar, "jewelry35", 1);
			dialog.text = "베네디치테! 진심으로 감사하오, 내 아들아. 그대가 성모 교회와 산티아고 본당을 위해 충실히 봉사해 준 것에 대해 말이오. 그대의 행위는 결코 보상받지 못하지 않을 것이오. 본당 신자들이 도둑맞은 물건을 되찾아 준 용감한 전사에게 드릴 헌금을 모았기에, 내가 기꺼이 그들을 대신하여 그대에게 주겠소. '일꾼이 그 삯을 받는 것은 마땅하도다.'";
			link.l1 = "감사합니다, 각하. 정말 기분 좋은 놀라움이군요!";
			link.l1.go = "utensil_2";
		break;
		
		case "utensil_2":
			GiveItem2Character(pchar, "chest");
			Log_Info("You've received a chest of doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "성모 교회에 충성스럽게 봉사하면 언제나 충실한 보상을 받게 되지. "+pchar.name+". 나는 그대가 기독교 세계의 방어와 수호를 위해 변함없는 전사가 되어 주기를 바라고 있소, 왜냐하면 우리 위에는 신화 속 다모클레스의 검처럼 치명적인 위협이 드리워져 있기 때문이오.";
			link.l1 = "그게 무엇이겠습니까, 각하?";
			link.l1.go = "utensil_3";
		break;
		
		case "utensil_3":
			dialog.text = "어쩌면 너는 다가오는 이 세상의 어둠의 권세와 세력에 맞선 전투에서 우리의 구원자가 될 운명일지도 모르겠구나, 아들아. 수많은 징조와 예언이 사악한 무언가가 다가오고 있음을 보여주고 있다네.";
			link.l1 = "징조와 예언인가?";
			link.l1.go = "utensil_4";
		break;
		
		case "utensil_4":
			dialog.text = "많지, 아들아... 그 중 하나는 네가 이교도 타야살의 잃어버린 인디언 금을 찾으려는 갈망이란다. 그들의 보물에 숨겨진 것이 바로 온 기독교 세계에 위협이 되는 것이기 때문이지.";
			link.l1 = "이 금에 대해 조금 더 설명해 주실 수 있겠습니까, 신부님? 이미 사라진 경위에 대한 이야기는 들었습니다만, 말씀하신 위협이란 대체 무엇입니까?";
			link.l1.go = "utensil_5";
		break;
		
		case "utensil_5":
			dialog.text = "잘 듣거라, 아들아. 지금부터 네가 듣게 될 모든 이야기는 오직 네 귀만을 위한 것이다. 미겔 디초소가 그 이교도의 보물을 고대 인디언 도시에서 꺼내오기 훨씬 전, 나는 이차 인디언 포로 한 명을 붙잡아 우리가 카리브 해에서 수행하는 임무에 대해 심문한 적이 있다. 이차족은 마야의 후손으로, 마야는 크리스토발 콜론과 그의 일행이 신세계에 처음 발을 들이기 훨씬 전, 수 세기 전에 이미 사라진 강대한 제국이었다. 마야 제국은 주변 부족들을 철권으로 다스렸고, 악마와의 지옥 같은 거래를 통해 얻은 말로 다 할 수 없는 힘을 휘둘렀다. 수 세대에 걸친 인신공양의 피로 산 어둠의 마법이었다. \n이 이차족 남자는 타야살, 즉 잃어버린 마야 도시와 그 안에 아직도 봉인된 엄청난 악에 대해 알고 있었다. 그는 자신이 아는 모든 것을 우리에게 말했다. 만약 그 봉인이 풀린다면, 그 결과는 세상의 종말과도 같을 것이다. 그때부터 나는 이 끔찍한 악이 깨어나는 것을 막기 위해 할 수 있는 모든 일을 해왔다. 나는 에스코리알과 로마에 편지를 써서 필사적으로 도움을 요청했다.\n그들은 내 말을 듣고 돈 라몬 데 멘도사 이 리바를 파견하여, 그가 프로비던스에 근거지를 세우고 타야살을 찾기 시작했다. 바로 그때 나는 선량한 돈 멘도사가... 잃어버린 도시를 찾는 동기가 다르다는 것을 알게 되었다. 그는 세상의 종말을 막으려 한 것이 아니라, 그리스도가 아닌 마몬을 섬기려 했던 것이다.\n그래서 하나님께서 그를 버리고 죽음의 천사를 그의 진영에 보내신 것이다. 그의 모든 행동은 헛되었고, 결국 스페인 병사들과 신앙을 받아들인 인디언 개종자들의 무의미한 죽음만을 초래했다. 나는 에스코리알에 라몬 데 멘도사를 무능력으로 해임해 달라고 다시 편지를 썼고, 그들은 그의 직무를 해제하는 데 동의했으나...";
			link.l1 = "Miguel Dichoso가 도착했다.";
			link.l1.go = "utensil_6";
		break;
		
		case "utensil_6":
			if (CheckAttribute(pchar, "questTemp.Dolly")) sTemp = "Kukulcan?! Sancta Maria, Mater Dei, ora pro nobis! Kukulcan again, that old serpent...";
			else sTemp = "Hm...";
			dialog.text = "정확히 그렇소. 저 악마가 보낸 모험가가 고대 마야의 보물들과 함께 타야살을 찾아냈지. 하지만 멘도사 돈의 기쁨은 오래가지 못했소. 그 모든 보물은 디초소와 함께 스페인으로 돌아가는 길에 사라져 버렸소. 아마도 모든 금괴와 장식품과 함께 미겔이 악마의 고대 근원, 쿠쿨칸이라 불리는 고대 마야 악신의 끔찍한 가면까지 가져간 것일 게요.";
			link.l1 = sTemp+"하지만 무슨 악행을 말씀하시는 겁니까, 각하? 그 사실을 어떻게 아셨습니까?";
			link.l1.go = "utensil_7";
		break;
		
		case "utensil_7":
			dialog.text = "이것은 카리브, 신세계, 어쩌면 구세계의 모든 세례받은 그리스도인들에게 죽음을 가져오는 악이오. 종말은 밤중에 도둑처럼 찾아올 것이며, 아무도 무슨 일이 일어났는지조차 깨닫지 못할 것이오. 그리고 이미 곳곳에 그 징조들이 나타나고 있소!";
			link.l1 = "무슨 징조 말인가? 이해가 안 되는데...";
			link.l1.go = "utensil_8";
		break;
		
		case "utensil_8":
			dialog.text = "아들아, 정말 그렇게 눈이 멀었느냐? 그것들이 스물다섯 해 동안, 거의 쉬지 않고 계속되고 있는 것도 모른단 말이냐!";
			link.l1 = "감히 말씀드리오, 각하, 제 삶의 기간은 바로 이 시간만큼으로 정확히 셈해질 뿐 아니라, 대부분의 세월을 유럽에서 보냈사옵니다. 제 무지는 어느 정도 용서받아야 마땅하오.";
			link.l1.go = "utensil_9";
		break;
		
		case "utensil_9":
			dialog.text = "알겠습니다. "+pchar.name+". 자네, 유럽에서 여기 카리브로 온 뒤로 이곳에서 이상한 일들이 벌어지고 있다는 걸 눈치채지 못했나? 마녀술, 흑마법, 그리고 다른 의식들이 본국보다 훨씬 더 강력한 힘을 지니고 있다는 게 이상하지 않나? 인디언 주술사들이 부여한 이교도 부적은, 누구든 손에 쥐기만 해도 그 힘을 분명히 느낄 수 있지.\n우리 기독교 연금술사들조차—신께서 그들의 잘못을 깨닫게 해주시길!—마법이 깃든 물건을 만드는 기술을 터득했네. 그들은 자신들이 그런 짓을 함으로써 악마를 섬기고 있다는 사실을 깨닫지 못하지. 자네, 시야 끝자락 어딘가에 지옥의 무언가가 도사리고 있다는 비정상적인 기운을 느끼지 못하나?";
			link.l1 = "아버지, 맞는 말씀입니다. 처음엔 저도 놀랐지만, 이제는 그냥 익숙해진 것 같아요... 결국 여긴 신세계니까요!";
			link.l1.go = "utensil_10";
		break;
		
		case "utensil_10":
			dialog.text = "하지만 항상 그랬던 것은 아니오. 내가 말하는 그 어둠은 약 25년 전에 이곳에 찾아왔고, 시간이 지날수록 점점 더 힘을 얻고 있소. 그 말은 단 하나를 의미하오. '그것'은 이미 왔고, '그것'은 우리 중에 있으며, '그것'은 이미 움직이고 있소...\n";
			link.l1 = "누구에 대해 말하는 거지? 그 신비로운 '그것'이 누구야?";
			link.l1.go = "utensil_11";
		break;
		
		case "utensil_11":
			dialog.text = "기독교인들의 맹렬한 적, 교회와 모든 그리스도교 세계의 파멸을 바라는 자.";
			link.l1 = "...혹시 적그리스도를 말하는 건가?";
			link.l1.go = "utensil_12";
		break;
		
		case "utensil_12":
			dialog.text = "그것이 '그' 적그리스도이든, 단지 '어떤' 적그리스도이든, 내가 감히 단정하진 않겠소. 이 짐승이 우리 구세주의 성육신을 흉내 내어 인간의 살을 두르고 나타날 때, 어떤 이름을 가지든 그건 중요하지 않소. 중요한 것은 이 존재가 무엇을 하려는가요. 나는 그것을 막으러 왔고, 자네는 나를 도와야 하오. 하지만 우리가 좀 흥분해서 이야기가 길어졌군. 자네는 행동하는 사람이니, 신학 이야기는 건너뛰고 바로 본론으로 들어가는 게 더 낫겠지, 맞소?";
			link.l1 = "오히려, 각하께로부터 새롭고 중요한 것들을 많이 배웠습니다. 더 들을 준비가 되어 있습니다.";
			link.l1.go = "utensil_13";
		break;
		
		case "utensil_13":
			dialog.text = "예의 바르고 잘 자란 아들이구나. 좋다. 이제, 나와 상의한 본래 이유로 돌아가자꾸나.\n우리 모두의 목표는 디초소가 가져간 타야살의 보물을 찾는 것이네. 그 보물 중에는 악마와의 다가오는 전투에서 쓸 수 있는 무기도 있을 것이네.";
			link.l1 = "하지만 혹시 디초소가 이미 카리브를 떠나 스페인에서 금더미 위에 앉아 있는 건 아닐까?";
			link.l1.go = "utensil_14";
		break;
		
		case "utensil_14":
			dialog.text = "아니. 이 보물들이 아직 카리브에 있다는 증거가 내게 있소. 내 정보원에 대해서는 아직 알 필요 없으니, 나를 믿으시오. 게다가, 나는 디초소가 남작에게 거짓말을 했다고 생각하오.\n타야살 유적에 관한 그의 이야기는 내가 심문한 이차 인디언이 말한 것과 맞지 않소. 게다가 디초소만이 모스키토 매복에서 유일하게 살아남았다는 것도 너무 수상하지 않소?";
			link.l1 = "돈 멘도사도 그렇게 생각하는 모양이군, 디초소를 찾으려고 생피에르를 습격한 걸 보면?";
			link.l1.go = "utensil_15";
		break;
		
		case "utensil_15":
			dialog.text = "남작의 행동은 네가 신경 쓸 일이 아니란다, 아들아. 그는 오직 금과 자신의 이익에 대한 욕망만으로 움직이고 있지. 그의 탐욕은 목에 매달린 맷돌처럼 그를 짓누를 것이며, 그 주변의 선한 그리스도인 남녀들은 지옥의 세력과 맞서 싸우고 있느니라.";
			link.l1 = "디초소와 보물을 어디서 찾아야 할지 단서라도 있나?";
			link.l1.go = "utensil_16";
		break;
		
		case "utensil_16":
			dialog.text = "나는 매 순간 그것을 생각하고 있단다, 아들아. 하지만 너에게 구체적으로 해줄 말은 없구나. 하지만 여기 우리를 도와줄 사람이 있다. 제노바 출신의 자연 철학자지. 나는 신의 사명을 위해 신세계의 유용한 것들을 분류하도록 그를 데려왔단다. 그는 이차 인디언의 심문을 목격했고, 내 판단으로는 그가 들은 것들이 그를 충격에 빠뜨렸고, 또 기이하게도 끌리게 만들었지.\n악마가 그의 호기심을 미끼 삼아 늑대덫처럼 그를 유혹했고, 그의 몸과 영혼을 사로잡았다. 주께서 그에게 의술과 연금술의 큰 재능을 주셨지만, 우리 제노바인은 결국 흑마법과 주술의 유혹에 빠지고 말았단다. 그는 내 허락 없이 내 포로인 이차와 여러 번 대화를 나누었고, 그러고는 사라졌지. 반드시 그를 찾아 그의 영혼을 구해야 한다.";
			link.l1 = "내가 그를 찾아야 한다는 말이군?";
			link.l1.go = "utensil_17";
		break;
		
		case "utensil_17":
			dialog.text = "그래, 아들아. 그는 우리가 우리를 위협하는 악의 세력에 맞서 쓸 수 있는 보물과 무기를 찾기 위한 첫걸음이란다.";
			link.l1 = "이 제노바인은 누구지?";
			link.l1.go = "utensil_18";
		break;
		
		case "utensil_18":
			dialog.text = "그의 이름은 지노 그비넬리다. 나이는 삼십 세쯤 되지. 뛰어난 의사이자 연금술사야. 내가 말했듯이, 지금은 흑마법을 연구하고 있지. 내가 얻은 최고의 정보에 따르면, 그는 지금 카리브 해의 영국 식민지 어딘가에 숨어 있다네.\n지노 그비넬리를 찾아라, 아들아. 우리 교회의 성물을 훔쳐간 그 해적도 찾아냈으니, 도망친 내 비서도 반드시 찾아서 이리 데려올 수 있을 게다. 성 안토니오께서 네게 은총을 베풀어 주시길 기도하마.";
			link.l1 = "알겠습니다, 각하. 더는 시간을 낭비하지 않겠습니다. 이따 뵙겠습니다!";
			link.l1.go = "utensil_19";
		break;
		
		case "utensil_19":
			DialogExit();
			AddQuestRecord("Guardoftruth", "35");
			bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win");
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && bOk)
			{
				pchar.questTemp.Guardoftruth = "jino";
				AddQuestUserData("Guardoftruth", "sText", "I almost betrayed myself by a shout of surprise. Father Vincento ordered me to find and bring him his runaway secretary, a physician alchemist named Gino Gvineili. That same Gino who occupies the spare room on the second floor of my house in St. John's!");
			}
			else
			{
				pchar.questTemp.Guardoftruth = "merdok";
				AddQuestUserData("Guardoftruth", "sText", "I must find a man named Gino Gvineili, hiding somewhere in the English Caribbean colonies. He is a physician and an alchemist. Where can a man like him hide?");
			}
		break;
		
		case "guardoftruth":
			dialog.text = "네가 그렇게 말할 줄 완전히 믿고 있었지, "+pchar.name+". 이제 당신이 신의 섭리에 의해 내게 보내졌다는 확신이 내 믿음을 더욱 굳건하게 해주었소. 내 불쌍하고 방탕한 아들은 어디 있소?";
			link.l1 = "듣기 싫은 소식일 것 같아 두렵지만, 어쩔 수 없습니다. 당신의 비서가 죽었습니다.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "신께서 그의 영혼을 구원하시고 죄를 용서해 주시길... 어떻게 된 일이냐, 아들아?";
			link.l1 = "나는 앤티과에서 지노를 찾았소. 그는 실험실 아래에 지어진 오래된 건물 중 하나에 숨어 있었지. 나와 조용히 함께 가는 걸 거부했소. 당신의 이름을 듣고 내가 무력을 쓸 준비가 되어 있다는 걸 보더니, 그는 긴 옷자락 속에서 맑은 액체가 든 작은 병을 꺼내 한순간에 마셔버렸소...\n";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "";
			link.l1 = "그리고 끔찍한 일이 일어났소: 그는 얼굴이 붉어지더니 곧 짙은 남색으로 변했소. 바닥에 쓰러져 경련을 일으키며 몸부림치다가, 얼마 지나지 않아 극심한 고통 속에서 죽었소. 방 안에는 강한 아몬드 냄새가 가득 퍼졌소.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "지노... 불쌍한 바보 같으니라고... 결국 자살이라는 죄를 지으며 마지막 순간까지 죄 속에 살았군. 참으로 비극적인 상실이야. 그의 영혼을 위해 기도하겠네...";
			link.l1 = "그가 죽은 후, 나는 그의 거처를 뒤져서 이 책을 발견했네. 혹시 자네에게 흥미가 있거나, 아니면 우리가 찾는 데 도움이 될 수도 있겠지? 여기에 뭔가 이상하고 난해한 메모들이 적혀 있더군...";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			RemoveItems(pchar, "Almanac", 1);
			Log_Info("You've given the almanac");
			PlaySound("interface\important_item.wav");
			dialog.text = "이건 가엾은 지노의 연감이란다. 그가 모든 탐험에 대해 여기에 메모를 남겼지. 이것을 내게 주렴, 아이야. 여기에 적힌 것을 내가 살펴보마. 어쩌면 실마리를 찾을 수 있을지도 모르지.\n비록 네가 지노 그비넬리를 내게 데려오진 못했지만, 나는 네 노력을 만족스럽게 여기고 있단다, 아이야. 이제 너에게 전할 소식이 있구나.";
			link.l1 = "제 관심을 끌었군요, 신부님.";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "나는 디초소의 프리깃함이 마지막으로 목격된 곳이 트리니다드 섬이라는 정보를 입수했네. 대략적인 시기도 알고 있지. 1654년 4월 초야.\n트리니다드로 가서 그 프리깃함의 행방에 대해 뭐든 알아보게. 어디로 향했는지, 선장이 무슨 계획을 가지고 있었는지, 알아낼 수 있는 건 뭐든 좋네. 시간이 오래 지났고 사람들의 기억에도 한계가 있다는 건 알지만, 물에 빠진 사람은 지푸라기라도 잡으려 하는 법이니.";
			link.l1 = "내 힘이 닿는 한 뭐든 하겠소.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "통행 허가서를 보여 주시오. 산호세 식민지 방문 허가도 추가해 주겠소.";
			link.l1 = "여기.";
			link.l1.go = "guardoftruth_6a";
		break;
		
		case "guardoftruth_6a":
			RemoveItems(pchar, "VerifyPaper", 1);
			dialog.text = "자, 이제 다 됐다. 네 배에 스페인 깃발 다는 것 잊지 마라. 앞으로 나아와 하나님의 축복을 받으렴, 아들아!";
			link.l1 = "잠시만 주십시오, 각하. 질문을 드려도 되겠습니까?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "네, 물론이지요. 무엇을 알고 싶으신가요?";
			link.l1 = "지난번 만남에서, 당신은 테야살에 대해 알려준 이차 인디언에 대해 이야기했지요.\n그 일에 대해 곰곰이 생각해 보았습니다... 말해 보시오, 그 남자에게 뭔가 지니고 있던 것이 있었소? 어떤 물건이라든지, 문서라든지, 그런 종류의 것 말이오?\n이게 도움이 될 수도 있소.";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "특별한 물건은 없었네, 아들아. 허름한 천 조각, 원시적인 장신구, 약초가 든 대나무 파이프, 그리고 재갈로 쓰인 거친 가죽 조각뿐이었지.\n이 모든 것은 돈 라몬 데 멘도사 이 리바에게 보내졌네. 하지만 분명히 말하건대, 흥미로운 것은 아무것도 없었네.";
			link.l1 = "알겠습니다. 감사합니다, 신부님. 다음에 또 뵙겠습니다!";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			DialogExit();
			GiveItem2Character(pchar, "VerifyPaper");
			ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper_A");
			AddQuestRecord("Guardoftruth", "38");
			npchar.quest.skinmap = "true";
			pchar.questTemp.Guardoftruth.Trinidad = "begin";
		break;
		
		case "guardoftruth_10":
			dialog.text = "전능하신 분께서 당신을 축복하시고 지켜주시길... 미겔 디초소는 어떻게 되었소? 알아냈소?";
			link.l1 = "유감스럽게도, 그렇지 않소. 마지막 목격자들이 말해준 것은 산타 키테리아 호가 강풍에 휩쓸려 마르티니크 쪽으로 떠밀려 갔다는 것뿐이오. 그 배가 무사했는지, 아니면 침몰했는지는 확실히 알 수 없소. 하지만 미겔 디초소가 살아남았을 거란 의심이 드는군.";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = "무엇이 너를 그렇게 결심하게 만들었느냐, 아들아?";
			link.l1 = "열쇠는 프리깃이 마르티니크 방향 어딘가에 숨어 있었다는 점이오. 그리고 아주 최근에, 돈 라몬 데 멘도사의 부하 중 한 명인 디에고 데 몬토야라는 용감한 카바예로가 미겔 디초소를 찾기 위해 생피에르를 공격했소. 그 미겔 디초소가 그곳에 숨어 있다고들 했지.";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = "그래서 남작은 디초소가 프랑스 놈들과 함께 숨었다고 생각하는군...";
			link.l1 = "저는 생피에르와 자크 디엘 뒤 파르케 총독을 잘 압니다, 각하. 그곳에는 미겔 디초소라는 스페인 사람을 아는 이가 아무도 없었습니다. 디에고 데 몬토야를 어떻게 찾을 수 있는지 말씀해 주시겠습니까? 디초소에 관해 그와 이야기하고 싶습니다.";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = "그가 너와 말할 생각이 정말 있다고 생각하느냐, 아들아? 내 생각엔, 칼과 권총으로 대화하지 않는 한 그럴 리 없을 것 같다.";
			link.l1 = "혹시 당신의 이름을 들으면 그가 좀 더 협조적으로 나오지 않을까요?";
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = "오, "+pchar.name+". 돈 멘도사의 충성스러운 부하가 너와 합의하려 할 것 같진 않군. 그에게 산디에고로 와서 나와 심문을 받으라고 명령하는 것도 한 방법이겠지만, 디에고가 나에게 완전히 솔직할지도 확신할 수 없어.";
			link.l1 = "이제 어떻게 해야 합니까, 아버지?";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "잠시 나를 내버려 두거라, 아들아. 네가 말한 것을 곱씹어 보고, 내가 이미 여러 경로로 알고 있던 사실들도 정리해야 하니. 그 후에 우리의 다음 행동을 알려주마. 나중에 다시 들르거라.";
			link.l1 = "예, 폐하. 알겠습니다. 주기적으로 보고드리겠습니다...";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			DialogExit();
			AddQuestRecord("Guardoftruth", "43");
			pchar.questTemp.Guardoftruth.Trinidad = "end";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setSpaOfficer.function = "GuardOT_SetSpaOfficerInTown";
			NextDiag.CurrentNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_wait":
			dialog.text = "신의 가호가 있기를, 아들아... 무엇을 도와줄까?";
			link.l1 = "각하, 소식이 있으신가요?";
			link.l1.go = "guardoftruth_wait_1";
		break;
		
		case "guardoftruth_wait_1":
			dialog.text = "지금은 아니란다, 아들아. 하지만 너무 낙심하지 마라. 나와 내 사람들이 그 일을 해결하려 애쓰고 있단다. 나중에 다시 들르거라.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_17":
			dialog.text = "그래, 아들아. 미겔 디초소에 대한 정보가 좀 있다. 내가 디초소가 아직 살아 있고 카리브에 있다고 믿은 것이 헛된 일이 아니었구나. 돈 디에고 데 몬토야가 옳았던 것 같아. 미겔 디초소의 얼굴을 알아본 한 남자로부터 확인을 받았는데, 실종된 그 신사가 1654년 4월, 산타 키테리아가 사라진 후 마르티니크의 르 프랑수아 해적 정착지에서 목격되었다고 하더구나...\n";
			link.l1 = "그래서 프리깃이 마르티니크 해안에서 침몰했단 말이오?";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "진정하거라, 아들아. 지금으로서는 그 시기에 마르티니크에서 난파된 어떤 배에 대한 정보도 없구나. 그리고 프리깃은 러거가 아니지. 그런 큰 배가 파괴됐다면 분명히 주목을 받았을 것이고, 현지의 시체 청소부들에게 엄청난 인양 기회를 제공했을 게야.";
			link.l1 = "해안과 해변을 수색해서 배의 잔해를 찾을 만한 가치가 있을까?";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "내 아들, 돈 디에고 데 몬토야도 이미 이 모든 일을 해봤으나 아무런 성과가 없었네. 계속 듣게. 내 프로비던스 쪽 정보원들에 따르면, 남작은 산타 키테리아가 여전히 다른 이름으로 카리브 해를 항해하고 있다고 확신하고 있다네.\n그래서 그가 미겔 디초소를 그토록 필사적으로 쫓는 것이지. 그의 말로는 산타 키테리아가 이슬라 테소로에서 멀지 않은 곳에서 목격되었고, 최근에는 영국 군함 편대의 호위를 받으며 영국 국기 아래에서 나타났다고 하네.";
			link.l1 = "뭐라고? 믿을 수가 없군. 그런 규모의 폭풍을 견디는 건 불가능하다고들 했는데... 그런데 산타 키테리아가 살아남았을 뿐만 아니라 지금은 영국 깃발 아래 항해하고 있다고? 두 사실이 맞지 않잖아. 대체 무슨 근거로 남작이 그 배가 산타 키테리아라고 확신한 거지? 정말 그렇게 특별한 배란 말인가?";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "아, 맞아요. 이 프리깃은 유럽의 최신 기술로 건조된 배요. 동급 치고는 무장이 아주 잘 되어 있고, 속도도 빨라서 화력이 더 센 적도 따돌릴 수 있소. 내 정보원이 그렇게 말했지.";
			link.l1 = "그리고 지금은 산타 키테리아라고 불리지 않나?";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = "그건 유감스럽게도 모르겠군... 이슬라 테소로로 가게. "+pchar.name+", 그리고 디초소의 프리깃에 대해 뭔가 알아내도록 해. 그렇게 하면 그 배의 전 선장도 찾을 수 있을지 몰라, 일석이조지. 아니면 쥐 두 마리를 한 덫에 잡는 셈이겠군.";
			link.l1 = "명 받들겠습니다, 각하!";
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "59");
			// проверяем, жив ли Акула и где он, если жив
			if (GetCharacterIndex("Dodson") != -1)
			{
				sld = characterFromId("Dodson");
				if (sld.location == "Pirates_townhall") pchar.questTemp.Guardoftruth.Archy = "islatesoro";
				else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			}
			else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			SetTimerCondition("Map_SetNationCoolHanters", 0, 0, 5, false); // немного развлечений
		break;
		
		case "tieyasal":
			dialog.text = "네가 나를 만나러 오기로 결심해서 기쁘구나, 아들아.";
			link.l1 = "안녕하십니까, 각하. 돈 알론소 데 말도나도와 만난 뒤로 다시 뵐 줄은 몰랐습니다.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "알론소 데 말도나도는 내 직접 명령을 어겼다. 나는 그가 너와 맞서는 것을 엄격히 금지했었지, 아들아, 그에게 어떤 결말이 닥칠지 이미 알고 있었으니까. 그리고 내가 예견한 일이 현실이 되었구나. 그의 임무는 너를 타야살까지 호위하는 것이었고, 그는 그곳에 가본 적이 있었다네.\n게다가 그의 함대와 스페인 병사 한 부대가 이차나 모스키토족의 공격으로부터 너를 지켜야 했지. 알론소는 복수심에 사로잡혀 옳지 못한 행동을 했다네.\n그는 타야살 원정에 실패했을 뿐 아니라, 자신에게 맡겨진 병사들과 배들까지 파멸로 이끌었고, 내게 불신과 원망의 씨앗을 네 마음에 심어 놓았다. 아들아, 나는 온전히 네 편임을 맹세하마. 우리는 이 어둠에 맞서 함께 서야 하네.";
			link.l1 = "나도 그렇게 믿고 싶군.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "안심하시오, "+pchar.name+". 나는 우리 주이시며 구세주이신 예수 그리스도의 충직하고 헌신적인 종이자 그분의 교회를 대표하는 자로서, 모든 영혼이 복된 주님의 말씀을 들을 기회를 얻기 전까지 세상의 종말을 막는 것 하나만을 목적으로 삼고 있소. 그러니 지금 악마에 사로잡힌 인디언의 손에 있는 그 사악한 유물을 반드시 막아야 하오. 나는 처음부터 이를 의심했으나, 이제야 완전히 확신하게 되었소. 그대는 주님께서 사탄과의 싸움에서 택하신 용사요.";
			link.l1 = "하지만 왜 그렇게 말씀하십니까, 아버지?";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "너는 내가 내 모든 첩자들과 함께 해도, 멘도사 남작이나 돈 디에고, 그리고 그 누구도 해내지 못한 일을 해냈군. 그 저주받은 섬을 찾아내고, 거기서 쿠쿨칸의 유물을 찾으러 갔지. 그렇지 않나?";
			link.l1 = "그래, 나는 쿠쿨칸의 가면을 가지고 있어.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "이 모든 일이 우연히 일어났다고 주장하려는 것이냐? 단순한 우연이라고? '사람이 마음으로 자기 길을 계획할지라도, 그 걸음을 인도하시는 이는 주님이시다.' 아들아, 전능하신 분께서 너를 이 길로 이끄셨다! 그분께서 전투에서 네 손을 강하게 하시고, 올바른 길로 네 발을 인도하셨으며, 위험한 때에 너를 지켜주셨다! '보라, 주님의 칼이 에돔에 심판을 내리러 내려오나니, 내가 멸망시키기로 작정한 그 백성 위에 내리리라!'\n";
			link.l1 = "에헴... 아버지, 하지만 임무는 사실상 이미 끝났습니다. 제가 가면을 가지고 있잖아요. 그 말은 쿠쿨칸이 빙의한 껍데기가 우리 역사에 들어와 바꿀 수 없다는 뜻 아닌가요...?";
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			dialog.text = "착각하고 있구나, 아들아. 그 악마는 이 가면이 있든 없든 저 문을 통과할 수 있다네. 가면은 단지 그가 사악한 짓을 더 쉽게 저지를 수 있게 해줄 뿐이지. 그를 막을 수 있는 유일한 방법은 지옥의 문을 완전히 파괴하는 것뿐이네.";
			link.l1 = "돈 알론소도 나에게 똑같이 말했지...";
			link.l1.go = "tieyasal_6";
		break;
		
		case "tieyasal_6":
			dialog.text = "그분 말씀이 옳았도다! 우리 주 예수 그리스도와 그분의 복되신 어머니의 이름으로, 이 악에 맞서 십자가를 들 것을 너에게 명하노라, 아들아! 네게 주어진 이 위대한 사명을 거부할 수는 없느니라. 나와 온 그리스도교 세계가 너를 믿고 있도다, 아들아.";
			link.l1 = "각하, 이건 너무하십니다. 정말... 몹시 난처하군요...";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "네 겸손함은 보기 좋구나, 아들아. 하지만 지금은 수줍은 처녀처럼 굴 때가 아니야. 마음을 약하게 먹거나 두려워하지 마라. 주 너의 하나님께서 앞서 가시며 너에게 승리를 주실 것이니! 사랑하는 이들을 위해, 모든 그리스도인을 위해 이 싸움에 나서거라... 만약 그들을 위해서가 아니라면 네 자신을 위해서라도 싸워야 한다. 저 악마가 승리하면 너도, 모두와 함께 멸망할 테니.";
			link.l1 = "아버지, 이제 저를 설득하신 것 같군요. 테야살 원정에 관해 제 처지를 망설였지만, 이제는 더 이상 의심이 없습니다. 무엇을 도와주실 수 있습니까?";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "타야살에 가는 길을 아는 자는 단 두 명뿐이었소: 알론소 데 말도나도와 미겔 디초소. 돈 알론소는 이미 죽었소. 그리고 디초소는... 최근에 이슬라 테소로의 샤프타운에서 목격됐다는 말을 들었소. 어쩌면 아직 그곳에 있을지도 모르지. 반드시 디초소를 찾아내 그를 안내자로 삼아야 하오.\n금이든 힘이든, 이 사내를 반드시 타야살로 데려가게 만들어야 하오. 그곳에서 지옥의 문을 발견하게 될 것이며, 그곳에서 그 문을 봉인해야 하오.";
			link.l1 = "그럼 남자들은?";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "내가 마지막으로 지휘했던 병사들은 알론소 데 말도나도의 지휘 아래 있었지. 안타깝게도 스페인 병사들로 또다시 부대를 꾸릴 기회는 없구나. 내가 이 지역 주둔군에서 신용을 다 써버렸거든. 이제는 네 부하들의 힘으로 해결해야 하네, 아들아. 하지만 다른 일이라면 내가 도울 수 있는 만큼 도와주마.";
			link.l1 = "무슨 도움이 필요하지?";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			dialog.text = "이번 싸움에서 우리는 물질적, 정신적으로 가질 수 있는 모든 이점을 활용해야 하네. 나는 아드리안 신부에게 다섯 날 후 이 예배당에서 나와 함께해 달라고 요청했네. 그는 자네를 위해 성스러운 부적을 가져올 것이네. 그 부적은 그리스도의 전사들에게 전투에서 도움이 될 걸세. 또한 자네에게 온갖 종류의 물약도 제공할 걸세. 나는 이 검을 받아주게, 아들아.\n이것은 기사단의 고대 검으로, 우리 조상들의 강력한 무기라네. 아직도 날카롭고, 교회의 축복으로 빛나고 있지. 오직 가장 위대한 기사들만이 이 검을 휘두를 영예를 누렸네. 자, 받아서 자랑스럽게 간직하게. 그리고 예수 그리스도의 이름을 입에 올리며 우리 신앙의 적들을 무찌르게!";
			link.l1 = "고마워! 이 검 정말 대단하네. 말이 안 나올 정도야...";
			link.l1.go = "tieyasal_11";
		break;
		
		case "tieyasal_11":
			sTemp = GetBestGeneratedItem("blade_32");
			GiveItem2Character(pchar, sTemp);
			sld = ItemsFromID(sTemp);
			sld.Balance = 2.0;
			sld.Weight = 4.5;
			Log_Info("You've received the Tanath");
			PlaySound("interface\important_item.wav");
			dialog.text = "신의 가호가 있기를, "+GetFullName(pchar)+", 이번 전투에서. 나는 너에게 성십자가의 가호를 내리노라. 승리가 머무는 손에 계시며 다윗에게 골리앗을 무찌를 기적의 힘을 주신 전능하신 하느님, 당신의 생명을 주는 자비로 이 무기들을 축복해 주시길 겸손히 기도하나이다; 그리고 당신의 종에게 허락하소서\n "+GetFullName(pchar)+" 그것을 지니고자 하는 자가 모든 보이는 적과 보이지 않는 적으로부터 성모 교회를 자유롭고 승리롭게 수호할 수 있도록 하소서. 우리 주 그리스도를 통하여 비나이다. 아멘.";
			link.l1 = "아멘!";
			link.l1.go = "tieyasal_12";
		break;
		
		case "tieyasal_12":
			dialog.text = "이제 가거라, 아들아. 하나님께서 너를 지켜주시고, 네가 찾는 길 위에서도, 네가 가는 길에서도, 전장에서도 결코 너를 떠나지 않으시길 빈다. 미겔 디초소를 찾아가 그의 도움으로 타야살로 가거라. 아드리안 신부도 잊지 마라, 그분이 필요한 부적과 약을 챙겨주실 것이다. 이제 나는 산티아고로 돌아가야 할 시간이구나. 잘 가거라, 아들아. 바야 콘 디오스.";
			link.l1 = "안녕히 계세요, 빈첸토 신부님...";
			link.l1.go = "tieyasal_13";
		break;
		
		case "tieyasal_13":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Tieyasal_VinsentoGo", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
