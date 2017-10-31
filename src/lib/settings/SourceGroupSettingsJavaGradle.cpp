#include "settings/SourceGroupSettingsJavaGradle.h"

SourceGroupSettingsJavaGradle::SourceGroupSettingsJavaGradle(const std::string& id, const ProjectSettings* projectSettings)
	: SourceGroupSettingsJava(id, SOURCE_GROUP_JAVA_GRADLE, projectSettings)
	, m_gradleProjectFilePath(FilePath())
	, m_gradleDependenciesDirectory(FilePath())
	, m_shouldIndexGradleTests(false)
{
}

SourceGroupSettingsJavaGradle::~SourceGroupSettingsJavaGradle()
{
}

void SourceGroupSettingsJavaGradle::load(std::shared_ptr<const ConfigManager> config)
{
	SourceGroupSettingsJava::load(config);

	const std::string key = s_keyPrefix + getId();

	setGradleProjectFilePath(FilePath(getValue<std::string>(key + "/gradle/project_file_path", "", config)));
	setGradleDependenciesDirectory(FilePath(getValue<std::string>(key + "/gradle/dependencies_directory", "", config)));
	setShouldIndexGradleTests(getValue<bool>(key + "/gradle/should_index_tests", false, config));
}

void SourceGroupSettingsJavaGradle::save(std::shared_ptr<ConfigManager> config)
{
	SourceGroupSettingsJava::save(config);

	const std::string key = s_keyPrefix + getId();

	setValue(key + "/gradle/project_file_path", getGradleProjectFilePath().str(), config);
	setValue(key + "/gradle/dependencies_directory", getGradleDependenciesDirectory().str(), config);
	setValue(key + "/gradle/should_index_tests", getShouldIndexGradleTests(), config);
}

bool SourceGroupSettingsJavaGradle::equals(std::shared_ptr<SourceGroupSettings> other) const
{
	std::shared_ptr<SourceGroupSettingsJavaGradle> otherJavaGradle = std::dynamic_pointer_cast<SourceGroupSettingsJavaGradle>(other);

	return (
		otherJavaGradle &&
		SourceGroupSettingsJava::equals(other) &&
		m_gradleProjectFilePath == otherJavaGradle->m_gradleProjectFilePath &&
		m_gradleDependenciesDirectory == otherJavaGradle->m_gradleDependenciesDirectory &&
		m_shouldIndexGradleTests == otherJavaGradle->m_shouldIndexGradleTests
	);
}

FilePath SourceGroupSettingsJavaGradle::getGradleProjectFilePath() const
{
	return m_gradleProjectFilePath;
}

FilePath SourceGroupSettingsJavaGradle::getGradleProjectFilePathExpandedAndAbsolute() const
{
	return m_projectSettings->makePathExpandedAndAbsolute(getGradleProjectFilePath());
}

void SourceGroupSettingsJavaGradle::setGradleProjectFilePath(const FilePath& path)
{
	m_gradleProjectFilePath = path;
}

FilePath SourceGroupSettingsJavaGradle::getGradleDependenciesDirectory() const
{
	return m_gradleDependenciesDirectory;
}

FilePath SourceGroupSettingsJavaGradle::getGradleDependenciesDirectoryExpandedAndAbsolute() const
{
	return m_projectSettings->makePathExpandedAndAbsolute(getGradleDependenciesDirectory());
}

void SourceGroupSettingsJavaGradle::setGradleDependenciesDirectory(const FilePath& path)
{
	m_gradleDependenciesDirectory = path;
}

bool SourceGroupSettingsJavaGradle::getShouldIndexGradleTests() const
{
	return m_shouldIndexGradleTests;
}

void SourceGroupSettingsJavaGradle::setShouldIndexGradleTests(bool value)
{
	m_shouldIndexGradleTests = value;
}